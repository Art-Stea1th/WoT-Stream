package 
{
	import flash.events.Event;
	import net.wg.infrastructure.base.AbstractWindowView;
	import net.wg.gui.components.controls.SoundButton;
	import net.wg.gui.components.controls.TextInput;
	import flash.text.*;	
	import scaleform.clik.events.ButtonEvent;
	
	public class WoTStreamView extends AbstractWindowView
	{		
		private var helpTextField    : TextField;
		private var tokenInput         : TextInput;
		private var startStopButton    : SoundButton;
		private var statusTextField    : TextField;
		
		public var CheckInput          : Function = null;
		public var StartStopStream     : Function = null;		
		
		public function WoTStreamView() 
		{
			super();
		}
		
		override protected function onPopulate() : void
        {
            super.onPopulate();
            width = 284;
            height = 110;
            window.title = "WoT-Stream: Remote";
			
			helpTextField = new TextField();
            helpTextField.width = 262;
            helpTextField.height = 50;
            helpTextField.x = 10;
            helpTextField.y = 10;
            helpTextField.multiline = false;
            helpTextField.selectable = false;
            helpTextField.defaultTextFormat = new TextFormat("$FieldFont", 14, 0xEBC386);
            helpTextField.text = "...";
			
            addChild(helpTextField);
			
			tokenInput = addChild(App.utils.classFactory.getComponent("TextInput", TextInput, {
                width: 152,
                height: 29,
                x: 10,
                y: 48
            })) as TextInput;
			
			tokenInput.addEventListener(Event.CHANGE, this.onTokenChanged);
			
			startStopButton = addChild(App.utils.classFactory.getComponent("ButtonRed", SoundButton, {
                width: 100,
                height: 25,
                x: 172,
                y: 50,
                label: "...",
				enabled: false
            })) as SoundButton;
			
			startStopButton.addEventListener(ButtonEvent.CLICK, this.onStartStreamClicked);
			
			statusTextField = new TextField();
			statusTextField.width = 262;
            statusTextField.height = 50;
            statusTextField.x = 10;
            statusTextField.y = 82;
            statusTextField.multiline = false;
            statusTextField.selectable = false;
            statusTextField.defaultTextFormat = new TextFormat("$FieldFont", 12, 0x969696);
            statusTextField.text = "status: ...";			
            addChild(statusTextField);
        }
		
		
		
		private function onTokenChanged(param: Event) : void {
			this.CheckInput(this.tokenInput.text);
		}
		
		private function onStartStreamClicked(param: ButtonEvent) : void {
			this.StartStopStream(this.tokenInput.text);
		}	
		
		
		
		public function SetHelpTextFieldText(helpText: String) : void {
			this.helpTextField.text = helpText;
		}
		
		public function SetTokenInputEnabled(enabled: Boolean) : void {
			this.tokenInput.enabled = enabled;
		}
		
		public function SetTokenInputText(text: String) : void {
			this.tokenInput.text = text;
		}
		
		public function SetStartStopButtonEnabled(enabled: Boolean) : void {
			this.startStopButton.enabled = enabled;
		}
		
		public function SetStartStopButtonLabel(label: String) : void {
			this.startStopButton.label = label;
		}
		
		public function SetStatusTextFieldText(statusText : String) : void {			
			this.statusTextField.text = "status: " + statusText;
		}
	}
}