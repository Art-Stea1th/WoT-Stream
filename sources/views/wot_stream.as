package 
{
	import net.wg.infrastructure.base.AbstractWindowView;
	import net.wg.gui.components.controls.SoundButton;
	import net.wg.gui.components.controls.TextInput;
	import flash.text.*;
	
	public class WoTStreamView extends AbstractWindowView
	{
		private var startStreamButton : SoundButton;
		private var stopStreamButton  : SoundButton;
		private var textFieldInfo     : TextField;
		private var tokenField        : TextInput;
		
		public function WoTStreamView() 
		{
			super();
		}
		
		override protected function onPopulate() : void
        {
            super.onPopulate();
            width = 290;
            height = 140;
            window.title = "WoT: Stream";
			
			textFieldInfo = new TextField();
            textFieldInfo.width = 270;
            textFieldInfo.height = 50;
            textFieldInfo.x = 10;
            textFieldInfo.y = 10;
            textFieldInfo.multiline = false;
            textFieldInfo.selectable = false;
            textFieldInfo.defaultTextFormat = new TextFormat("$FieldFont", 14, 0xEBC386);
            textFieldInfo.text = "Enter your token below and click \"Start Stream\"!";
            addChild(textFieldInfo);
			
			tokenField = addChild(App.utils.classFactory.getComponent("TextInput", TextInput, {
                width: 160,
                height: 29,
                x: 10,
                y: 68
            })) as TextInput;
			
			startStreamButton = addChild(App.utils.classFactory.getComponent("ButtonRed", SoundButton, {
                width: 100,
                height: 25,
                x: 180,
                y: 70,
                label: "Start Stream"
            })) as SoundButton;
			
			stopStreamButton = addChild(App.utils.classFactory.getComponent("ButtonNormal", SoundButton, {
                width: 100,
                height: 25,
                x: 180,
                y: 105,
                label: "Stop Stream"
            })) as SoundButton;
        }		
	}
}