#from gui.Scaleform.framework import g_entitiesFactories, ViewSettings
#from gui.Scaleform.framework import ViewTypes, ScopeTemplates
#from gui.Scaleform.framework.entities.abstract.AbstractWindowView import AbstractWindowView
#from gui.app_loader import g_appLoader
#from gui.shared.utils.key_mapping import getBigworldNameFromKey

#class TestWindow(AbstractWindowView):

#    def __init__(self):
#        super(TestWindow, self).__init__()

#    def _populate(self):
#        super(TestWindow, self)._populate()

#    def onWindowClose(self):
#        self.destroy()


#_alias = 'TestWindow'
#_url = 'TestWindow.swf'
#_type = ViewTypes.WINDOW
#_event = None
#_scope = ScopeTemplates.VIEW_SCOPE


#_settings = ViewSettings(_alias, TestWindow, _url, _type, _event, _scope)
#g_entitiesFactories.addSettings(_settings)

#def onhandleKeyEvent(event):
#    key = getBigworldNameFromKey(event.key)
#    if key == 'KEY_F10':
#        g_appLoader.getDefLobbyApp().loadView(_alias)
#    return None

#from gui import InputHandler
#InputHandler.g_instance.onKeyDown += onhandleKeyEvent