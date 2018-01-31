from ctypes import *
from pathlib import Path
from os import chdir

class WoTStreamController(object):

    def __init__(self, lib_full_name):
        self.lib = WinDLL(self.name, RTLD_GLOBAL)

    def initialize(self):
        self.lib.initialize()

    def start_stream(self):
        self.lib.start_stream()

    def stop_stream(self):
        self.lib.stop_stream()

    def shutdown(self):
        self.lib.shutdown()

def main():

    controller = WoTStreamController('..\\..\\build\\Debug\\wot_stream.dll')
    controller.initialize()
    input()

    controller.start_stream()
    input()

    controller.stop_stream()
    input()

    controller.shutdown()

if __name__ == "__main__":
    main()


# _+_+_+_+_+_+_+_+_+_+_+_+_ MOD-CODE-BELOW _+_+_+_+_+_+_+_+_+_+_+_+_

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

class WoTStreamView(LobbySubView, WindowViewMeta):

    def __init__(self):
        View.__init__(self)

    def _populate(self):
        View._populate(self)

    def _dispose(self):
        View._dispose(self)

    def onTryClosing(self):
        return True

    def onWindowClose(self):
        self.destroy()

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
        print(key)
    return None


def new_init(self, swf, className='Flash', args=None, path=SCALEFORM_SWF_PATH):
    old_init(self, swf, className, args, path)
    if swf == 'lobby.swf':
        self.addListener(events.AppLifeCycleEvent.INITIALIZED, lambda e: subscribe(self, e))
        

def subscribe(self, event):
    InputHandler.g_instance.onKeyDown += on_key_event

Flash.__init__ = new_init