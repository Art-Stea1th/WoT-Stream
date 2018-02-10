import re
import atexit
import subprocess
from os import path
from socket import socket

from gui import InputHandler
from gui.Scaleform.framework import g_entitiesFactories, ViewSettings, ViewTypes, ScopeTemplates
from gui.Scaleform.framework.entities.View import View
from gui.Scaleform.framework.managers.loaders import ViewLoadParams
from gui.app_loader.loader import g_appLoader
from gui.shared.utils.key_mapping import getBigworldNameFromKey


def wsrLogInfo(message):
    wsrLog('INFO', message)

def wsfLogWarning(message):
    wsrLog('WARNING', message)

def wsrLogError(message):
    wsrLog('ERROR', message)

def wsrLogUnexpected(message):
    wsrLog('UNEXPECTED', message)

def wsrLog(level, message):
    if level and message:
        print getWSRLogSuffix() + level + ': ' + str(message)

def getWSRLogSuffix():
    return 'WSR-'


class Protocol(object): # I Want Enums

    def __init__(self):

        # ordinary responses
        self.__ok = 'ok'
        self.__bp = 'bp'
        self.__er = 'er'
        self.__uw = 'uw'

        # 'stat' responses
        self.__ntin = 'ntin'
        self.__stpd = 'stpd'
        self.__busy = 'busy'
        self.__srtd = 'srtd'

    # ordinary responses

    @property
    def ok(self):
        return self.__ok

    @property
    def badOperation(self):
        return self.__bp

    @property
    def error(self):
        return self.__er

    @property
    def unawailable(self):
        return self.__uw

    # 'stat' responses

    @property
    def notInitialized(self):
        return self.__ntin

    @property
    def started(self):
        return self.__srtd

    @property
    def busy(self):
        return self.__busy

    @property
    def stopped(self):
        return self.__stpd
    

class WoTStreamRemote(object):

    def __init__(self, address, port):
        self.__proto = Protocol()
        self.__address = address
        self.__port = port
        self.__sc = None
        self.__wsr = None
        self.connect()
        self.initialize()

    @property
    def proto(self):
        return self.__proto

    def connect(self):
        if self.__connect() == self.proto.unawailable:
            if self.__startWoTStream() == self.proto.unawailable:
                return self.proto.unawailable
            return self.__connect()
        return self.proto.ok
    
    def getState(self):
        return self.__safeRemoteExec('stat', 4)

    def initialize(self):
        return self.__safeRemoteExec('init')

    def updateToken(self, token):
        return self.__safeRemoteExec('updt: ' + token)

    def startStream(self):
        return self.__safeRemoteExec('srts')

    def stopStream(self):
        return self.__safeRemoteExec('stps')    

    def __safeRemoteExec(self, command, response_length=2):
        try:
            return self.__send(command, response_length)
        except:
            return self.__proto.unawailable

    def __send(self, command, response_length):
        self.__sc.send(command)
        return self.__sc.recv(response_length)

    def __connect(self):
        wsrLogInfo('try connect to wot_stream')
        try:
            self.__sc = socket()
            self.__sc.connect((self.__address, self.__port))
            wsrLogInfo('connection successful')
            return self.proto.ok
        except:
            wsrLogError("can't connect to wot_stream")
        return self.proto.unawailable

    def __startWoTStream(self):
        wsrLogInfo('try start wot_stream')
        if self.getState() == self.proto.unawailable:
            wsr_path = path.abspath(path.join(__file__,  r'../../../../../wot_stream/'))
            full_name = wsr_path + r'\wot_stream.exe'
            sinfo = subprocess.STARTUPINFO()
            sinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
            try:
                wsr = subprocess.Popen(full_name, cwd=wsr_path, startupinfo=sinfo)
                atexit.register(wsr.kill)
                wsrLogInfo('wot_stream started')
            except:
                wsrLogError("can't start wot_stream")
                return self.proto.unawailable
        else:
            wsrLogInfo('wot_stream already started')
        return self.proto.ok


class WotStreamViewState(object):

    def __init__(self):
        self.WSR = WoTStreamRemote('127.0.0.1', 48684)
        self.pattern = re.compile(r'^[a-z0-9]{4,4}-[a-z0-9]{4,4}-[a-z0-9]{4,4}-[a-z0-9]{4,4}', re.IGNORECASE)

        self.helpText = "Enter your token below and click 'Start Stream'!"
        self.inputEnabled = True
        self.inputText = ''
        self.btnEnabled = False
        self.btnLabel = 'Start Stream'
        self.statusText = 'unknown'


g_ws_ViewState = WotStreamViewState()

def getViewState():
    global g_ws_ViewState
    return g_ws_ViewState


class WoTStreamView(View):

    def __init__(self):
        super(WoTStreamView, self).__init__()
        self.__state = getViewState()
        self.WSR = self.__state.WSR
        self.proto = self.WSR.proto
        wsrLogInfo('init ok')

    def _populate(self):
        super(WoTStreamView, self)._populate()

    def onFocusIn(self, alias):
        super(WoTStreamView, self).onFocusIn(alias)
        self.__loadState()

    def onTryClosing(self):
        return True

    def onWindowClose(self):
        self.destroy()

    def _dispose(self):
        super(WoTStreamView, self)._dispose()

    def __del__(self):
        super(WoTStreamView, self).__del__()

    def __loadState(self):
        self.__changeViewData(
            help_text     = self.__state.helpText,
            input_enabled = self.__state.inputEnabled,
            input_text    = self.__state.inputText,
            btn_enabled   = self.__state.btnEnabled,
            btn_label     = self.__state.btnLabel,
            status_text   = self.__state.statusText)

    # -- from view
    def checkInput(self, input):

        input_valid = False

        if input and len(input) == 19:
            match = self.__state.pattern.match(input)
            if match:
                self.__state.inputText = match.group(0)
                input_valid = True

        self.__onInputValidate(input_valid)

    # -- from view
    def startStopStream(self, token):
        
        state = self.WSR.getState()

        if state == self.proto.unawailable:
            self.__onConnect(self.WSR.connect())            

        elif state == self.proto.notInitialized:
            self.__onInitialize(self.WSR.initialize())            

        elif state == self.proto.stopped:
            self.WSR.updateToken(self.__state.inputText)
            self.__onStreamStart(self.WSR.startStream())            

        elif state == self.proto.busy:
            self.__onBusy()

        elif state == self.proto.started:
            self.__onStreamStop(self.WSR.stopStream())            
        else:
            wsrLogUnexpected('unexpected "wot_stream.getState" response')

    def __onConnect(self, result):
        self.__changeViewData(input_enabled=False, btn_enabled=True)
        if result == self.proto.ok:
            self.__changeViewData(
                help_text     = "Connected, click 'Initialize'",
                btn_label     = 'Initialize',
                status_text   = 'connection successfully')
        else:
            self.__changeViewData(
                help_text     = "Run the companion app and click 'Connect'",
                btn_label     = 'Try Again',
                status_text   = "connection failed, wot_stream.exe isn't available")


    def __onInitialize(self, result):
        if result == self.proto.ok:
            self.__changeViewData(
                help_text     = "Enter your token below and click 'Start Stream'!",
                input_enabled = True,
                btn_enabled   = False,
                btn_label     = 'Start Stream',
                status_text   = 'initialization completed successfully')
        else:
            self.__changeViewData(
                help_text     = "Run the companion app and click 'Connect'",
                input_enabled = False,
                btn_enabled   = True,
                btn_label     = 'Try Again',
                status_text   = 'initialization failed, something went wrong')


    def __onStreamStart(self, result):
        self.__changeViewData(input_enabled=True, btn_enabled=True)
        if result == self.proto.ok:
            self.__changeViewData(
                help_text     = "Stream started! You can close this window",
                input_enabled = False,
                btn_label     = 'Stop Stream',
                status_text   = 'stream started',
                log_msg       = 'stream started')
        elif result == self.proto.error: #invalid token
            self.__changeViewData(
                help_text     = "Couldn't start the stream",
                btn_label     = 'Try Again',
                status_text   = "Invalid stream token or rtmp-server isn't available",
                log_msg       = "start stream fail, bad token or rtmp-server isn't available")
        else:
            self.__changeViewData(
                help_text     = "Couldn't start the stream",
                btn_label     = 'Try Again',
                status_text   = 'wot stream not ready',
                log_msg       = 'start stream fail, wot stream not ready')


    def __onBusy(self):
        self.__changeViewData(
                help_text     = "Operation failed",
                input_enabled = True,
                btn_enabled   = True,
                btn_label     = 'Try Again',
                status_text   = 'wot stream not ready',
                log_msg       = 'busy, operation failed, wot stream not ready')


    def __onStreamStop(self, result):
        self.__changeViewData(input_enabled=True, btn_enabled=True)
        if result == self.proto.ok:
            self.__changeViewData(
                help_text     = "Stream stopped!",
                btn_label     = 'Start Stream',
                status_text   = 'stream stopped',
                log_msg       = 'WSR: stream stopped')
        else:
            self.__changeViewData(
                help_text     = "Could not stop the stream",
                btn_label     = 'Try Again',
                status_text   = 'wot stream not ready',
                log_msg       = 'stop stream fail, wot stream not ready')


    def __onInputValidate(self, input_valid):
        if input_valid:
            self.__setStatusText('token valid')
            self.__setBtnLabel('Start Stream')
        else:
            self.__setStatusText('invalid token')
        self.__setBtnEnabled(input_valid)

    
    def __changeViewData(self, help_text=None,
                         input_enabled=None, input_text=None,
                         btn_enabled=None, btn_label=None,
                         status_text=None, log_msg=None):
        if help_text is not None:
            self.__setHelpText(help_text)
        if input_enabled is not None:
            self.__setInputEnabled(input_enabled)
        if btn_enabled is not None:
            self.__setBtnEnabled(btn_enabled)
        if btn_label is not None:
            self.__setBtnLabel(btn_label)
        if status_text is not None:
            self.__setStatusText(status_text)
        if log_msg is not None:
            wsrLogInfo(log_msg)

    # -- to view
    def __setHelpText(self, help_text):
        self.__state.helpText = help_text
        self.flashObject.SetHelpTextFieldText(help_text)

    # -- to view
    def __setInputEnabled(self, input_enabled):
        self.__state.inputEnabled = input_enabled
        self.flashObject.SetTokenInputEnabled(input_enabled)

    # -- to view
    def __setInputText(self, input_text):
        self.__state.inputText = input_text
        self.flashObject.SetTokenInputText(input_text)

    # -- to view
    def __setBtnEnabled(self, btn_enabled):
        self.__state.btnEnabled = btn_enabled
        self.flashObject.SetStartStopButtonEnabled(btn_enabled)

    # -- to view
    def __setBtnLabel(self, btn_label):
        self.__state.btnLabel = btn_label
        self.flashObject.SetStartStopButtonLabel(btn_label)

    # -- to view
    def __setStatusText(self, status_text):
        self.__state.statusText = status_text
        self.flashObject.SetStatusTextFieldText(status_text)


_window_alias = 'WotStreamView'
_url = 'wot_stream.swf'
_type = ViewTypes.WINDOW
_event = None
_scope = ScopeTemplates.GLOBAL_SCOPE

_settings = ViewSettings(_window_alias, WoTStreamView, _url, _type, _event, _scope)
g_entitiesFactories.addSettings(_settings)


def init():
    InputHandler.g_instance.onKeyDown += on_key_event

def fini():
    InputHandler.g_instance.onKeyDown -= on_key_event


def on_key_event(event):
    key = getBigworldNameFromKey(event.key)
    if key == 'KEY_F10':
        app = g_appLoader.getApp().loadView(ViewLoadParams(_window_alias, _window_alias))