package
{
    import net.wg.infrastructure.base.AbstractWindowView;

    public class TestWindow extends AbstractWindowView
    {
        public function TestWindow()
        {
            super();
        }

        override protected function onPopulate() : void
        {
            super.onPopulate();
            width = 600;
            height = 400;
            window.title = "Test Window";
        }
    }
}