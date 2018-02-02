package 
{
	import net.wg.infrastructure.base.AbstractWindowView;
	import net.wg.gui.components.controls.SoundButton;
	import net.wg.gui.components.controls.TextInput;
	import flash.text.*;
	
	import scaleform.clik.events.ButtonEvent;
	
	public class WoTStreamView extends AbstractWindowView
	{
		private var tokenBuffer       : String = "Hello!";
		
		private var startStreamButton : SoundButton;
		// private var stopStreamButton  : SoundButton;
		private var textFieldInfo     : TextField;
		private var tokenField        : TextInput;
		
		public var startStream        : Function = null;
		
		
		
		public function WoTStreamView() 
		{
			super();
		}
		
		override protected function onPopulate() : void
        {
            super.onPopulate();
            width = 284;
            height = 87;
            window.title = "WoT: Stream";
			
			textFieldInfo = new TextField();
            textFieldInfo.width = 262;
            textFieldInfo.height = 50;
            textFieldInfo.x = 10;
            textFieldInfo.y = 10;
            textFieldInfo.multiline = false;
            textFieldInfo.selectable = false;
            textFieldInfo.defaultTextFormat = new TextFormat("$FieldFont", 14, 0xEBC386);
            textFieldInfo.text = "Enter your token below and click \"Start Stream\"!";
            addChild(textFieldInfo);
			
			tokenField = addChild(App.utils.classFactory.getComponent("TextInput", TextInput, {
                width: 152,
                height: 29,
                x: 10,
                y: 48
            })) as TextInput;
			
			startStreamButton = addChild(App.utils.classFactory.getComponent("ButtonRed", SoundButton, {
                width: 100,
                height: 25,
                x: 172,
                y: 50,
                label: "Start Stream"
            })) as SoundButton;
			
			startStreamButton.addEventListener(ButtonEvent.CLICK, this.onStartStreamClick);
        }
		
		private function onStartStreamClick(param:ButtonEvent) : void {
			this.startStream(this.tokenBuffer);
		}
	}
}