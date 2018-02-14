from gui import InputHandler
from gui.Scaleform.framework import g_entitiesFactories, ViewSettings, ViewTypes, ScopeTemplates
from gui.Scaleform.framework.entities.View import View
from gui.Scaleform.framework.managers.loaders import ViewLoadParams
from gui.app_loader.loader import g_appLoader
from gui.shared.utils.key_mapping import getBigworldNameFromKey

from wot_stream_view_model import *

_window_alias = 'WotStreamView'
_url = 'wot_stream.swf'
_type = ViewTypes.WINDOW
_event = None
_scope = ScopeTemplates.GLOBAL_SCOPE

_settings = ViewSettings(_window_alias, WoTStreamViewModel, _url, _type, _event, _scope)
g_entitiesFactories.addSettings(_settings)


def init():
    InputHandler.g_instance.onKeyDown += on_key_event

def fini():
    InputHandler.g_instance.onKeyDown -= on_key_event


def on_key_event(event):
    key = getBigworldNameFromKey(event.key)
    if key == 'KEY_F10':
        app = g_appLoader.getApp().loadView(ViewLoadParams(_window_alias, _window_alias))