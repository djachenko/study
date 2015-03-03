using GUI.ViewModels;

namespace GUI.Views
{
    public sealed partial class AboutDialog
    {
        public AboutDialog()
        {
            InitializeComponent();

            DataContext = new AboutDialogViewModel();
        }
    }
}
