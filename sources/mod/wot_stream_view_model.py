import re

from gui.Scaleform.framework.entities.View import View

from wot_stream_remote import *


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


class WoTStreamViewModel(View):

    def __init__(self):
        super(WoTStreamViewModel, self).__init__()
        self.__state = getViewState()
        self.WSR = self.__state.WSR
        self.proto = self.WSR.proto
        wsrLogInfo('init ok')

    def _populate(self):
        super(WoTStreamViewModel, self)._populate()

    def onFocusIn(self, alias):
        super(WoTStreamViewModel, self).onFocusIn(alias)
        self.__loadState()

    def onTryClosing(self):
        return True

    def onWindowClose(self):
        self.destroy()

    def _dispose(self):
        super(WoTStreamViewModel, self)._dispose()

    def __del__(self):
        super(WoTStreamViewModel, self).__del__()

    def __loadState(self):
        self.__changeViewData(
            help_text     = self.__state.helpText,
            input_enabled = self.__state.inputEnabled,
            input_text    = self.__state.inputText,
            btn_enabled   = self.__state.btnEnabled,
            btn_label     = self.__state.btnLabel,
            status_text   = self.__state.statusText)

    # -- from view
    def debugPrint(self, message):
        wsrLogInfo(message)

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