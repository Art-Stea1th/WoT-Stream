from gui.app_loader.loader import g_appLoader
from gui.Scaleform import SCALEFORM_SWF_PATH
from gui.Scaleform.daapi import LobbySubView
from gui.Scaleform.daapi.view.meta.WindowViewMeta import *
from gui.Scaleform.Flash import Flash
from gui.Scaleform.framework import g_entitiesFactories, ViewSettings, ViewTypes, ScopeTemplates
from gui.Scaleform.framework.entities.View import View
from gui.Scaleform.framework.managers.loaders import ViewLoadParams
from gui.shared import events
from gui.shared.utils.key_mapping import getBigworldNameFromKey
from gui import InputHandler

LobbySubView.__background_alpha__ = 0

# ---------------------------------------------------------------------------------------------------------------------------

from socket import socket
from warnings import warn

class ServerState(object):
    def __init__(self):
        self.__ok = 0
        self.__rd = 1
        self.__er = 255
    @property
    def Ok(self):
        return self.__ok
    @property
    def Error(self):
        return self.__er
    @property
    def ReadyToReceive(self):
        return self.__rd

class WoTStreamRemote(object):

    def __init__(self, address, port):

        # inline protocol
        self.__state = ServerState()

        # other fields
        self.__address = address
        self.__port = port
        self.__stream_started = False
        self.__sc = socket()
        self.__sc.connect((address, port))

    def Initialize(self):
        self.__send(0)

    @property
    def PingOk(self):
        try:
            self.__sendCommand(1)
            return True
        except:
            return False

    @property
    def StreamStarted(self):
        response = self.__send(1)
        if response == 0:
            self.__stream_started = False
        else:
            self.__stream_started = True
        return self.__stream_started

    def StartStream(self, token):
        self.__send(2, token)

    def StopStream(self):
        self.__send(3)

    def Shutdown(self):
        self.__send(4)
        self.__sc.close()

    def __send(self, command, data=None):
        response = self.__state.Error
        if data:
            response = self.__sendCommand(command)
            if response == self.__state.ReadyToReceive:
                response = self.__sendData(data)
                if response != self.__state.Ok:
                    warn('server ready to receive, but data not accepted')
            else:
                warn('the command contains data but the server didn\'t ready to accept')
        else:
            response = self.__sendCommand(command)
        return response
        

    def __sendCommand(self, command):

        if command == None:
            raise ValueError('command must be a byte')

        cmd = str(int(command))[0]
        self.__sc.send(cmd)

        response = self.__decodeResponse(self.__sc.recv(1))
        if response != self.__state.Ok and response != self.__state.ReadyToReceive:
            warn('the command execution didn\'t confirmed by the server')

        return response
        

    def __sendData(self, data):

        if data == None:
            raise ValueError('data string can\'t be \'None\' or empty')

        self.__sc.send(data)
        response = self.__decodeResponse(self.__sc.recv(1))
        if response != self.__state.Ok:
            warn('the data receiving didn\'t confirmed by the server')

        return response

    def __decodeResponse(self, value):
        try:
            response = int(value)
            if response == 0 \
            or response == 1 \
            or response == 255:
                return response
            raise
        except:
            return 255

# ---------------------------------------------------------------------------------------------------------------------------

import re

class WotStreamViewState(object):

    def __init__(self):
        self.WSR = None
        self.Pattern = re.compile('^[a-z0-9]{4,4}-[a-z0-9]{4,4}-[a-z0-9]{4,4}-[a-z0-9]{4,4}', re.IGNORECASE)

        self.Help = 'Run the companion app and click \'Connect\''
        self.InputEnabled = False
        self.Token = ''
        self.BtnEnabled = True
        self.BtnLabel = 'Connect'
        self.StatusText = 'unknown'

g_ws_ViewState = WotStreamViewState()

class WoTStreamView(LobbySubView, WindowViewMeta):

    def __init__(self):
        View.__init__(self)
        global g_ws_ViewState
        self.__state = g_ws_ViewState
        self.__after_init = True
        print 'WSR: View --- init ok'

    def onFocusIn(self, alias):
        self.__loadState()

    def onTryClosing(self):
        return True

    def onWindowClose(self):
        self.destroy()

    def _dispose(self):
        View._dispose(self)

    def __loadState(self):
        self.__setHelpText(self.__state.Help)        
        self.__setInputEnabled(self.__state.InputEnabled)
        self.__setInputText(self.__state.Token)
        self.__setBtnEnabled(self.__state.BtnEnabled)
        self.__setBtnLabel(self.__state.BtnLabel)
        self.__setStatusText(self.__state.StatusText)
        print 'WSR: View --- state loaded'

    # -- from view
    def CheckInput(self, input):

        input_valid = False

        if input and len(input) == 19:
            match = self.__state.Pattern.match(input)
            if match:
                self.__state.Token = match.group(0)
                input_valid = True

        self.__onInputValidate(input_valid)

    # -- from view
    def StartStopStream(self, token):
        if self.__wsrReady():

            if self.__after_init:
                self.CheckInput(token)
                return

            if self.__streamStarted():
                self.__stopStream()
            else:
                self.__startStream(token)
        else:
            pass

    def __startStream(self, token):
        self.__state.WSR.StartStream(token)
        self.__onStreamStarted()

    def __stopStream(self):
        self.__state.WSR.StopStream()
        self.__onStreamStopped()

    # --

    def __wsrReady(self):
        ready = False
        try:
            if not self.__state.WSR or not self.__state.WSR.PingOk:
                self.__state.WSR = WoTStreamRemote('127.0.0.1', 48684)
                self.__state.WSR.Initialize()
                self.__after_init = True
            else:
                self.__after_init = False
            ready = True
        except:
            ready = False
        self.__onWSRCheck(ready)
        return ready

    def __streamStarted(self):
        try:
            if self.__state.WSR and self.__state.WSR.StreamStarted:
                return True
            return False
        except:
            return False

    def __onWSRCheck(self, ready):
        if ready:
            self.__setHelpText('Enter your token below and click \'Start Stream\'!')
            self.__setStatusText('wot stream remote ready')
        else:
            self.__setHelpText('Run the companion app and click \'Connect\'')
            self.__setBtnLabel('Connect')
            self.__setStatusText('wot stream remote unawailable, try again')
        self.__setInputEnabled(ready)


    def __onInputValidate(self, valid):
        if valid:
            self.__setStatusText('token valid')
            self.__setBtnLabel('Start Stream')
        else:
            self.__setStatusText('invalid token')
        self.__setBtnEnabled(valid)

    def __onStreamStarted(self):
        self.__setInputEnabled(False)
        self.__setBtnEnabled(True)
        self.__setBtnLabel('Stop Stream')
        self.__setStatusText('stream started')

    def __onStreamStopped(self):
        self.__setInputEnabled(True)
        self.__setBtnEnabled(True)
        self.__setBtnLabel('Start Stream')
        self.__setStatusText('stream stopped')

    # -- to view
    def __setHelpText(self, text):
        self.__state.Help = text
        self.flashObject.SetHelpTextFieldText(text)

    # -- to view
    def __setInputEnabled(self, enabled):
        self.__state.InputEnabled = enabled
        self.flashObject.SetTokenInputEnabled(enabled)

    # -- to view
    def __setInputText(self, text):
        self.__state.Token = text
        self.flashObject.SetTokenInputText(text)

    # -- to view
    def __setBtnEnabled(self, enabled):
        self.__state.BtnEnabled = enabled
        self.flashObject.SetStartStopButtonEnabled(enabled)

    # -- to view
    def __setBtnLabel(self, label):
        self.__state.BtnLabel = label
        self.flashObject.SetStartStopButtonLabel(label)

    # -- to view
    def __setStatusText(self, text):
        self.__state.StatusText = text
        self.flashObject.SetStatusTextFieldText(text)


_window_alias = 'WotStreamView'
_url = 'wot_stream.swf'
_type = ViewTypes.WINDOW
_event = None
_scope = ScopeTemplates.GLOBAL_SCOPE

_settings = ViewSettings(_window_alias, WoTStreamView, _url, _type, _event, _scope)
g_entitiesFactories.addSettings(_settings)

old_init = Flash.__init__

def on_key_event(event):
    key = getBigworldNameFromKey(event.key)
    if key == 'KEY_F10':
        g_appLoader.getApp().loadView(ViewLoadParams(_window_alias, _window_alias))

def new_init(self, swf, className='Flash', args=None, path=SCALEFORM_SWF_PATH):
    old_init(self, swf, className, args, path)
    if swf == 'lobby.swf':
        self.addListener(events.AppLifeCycleEvent.INITIALIZED, lambda e: subscribe(self, e))

def subscribe(self, event):
    InputHandler.g_instance.onKeyDown += on_key_event

Flash.__init__ = new_init