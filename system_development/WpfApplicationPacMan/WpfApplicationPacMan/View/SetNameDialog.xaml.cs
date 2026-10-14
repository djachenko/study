using System.Windows;

namespace WpfApplicationPacMan.View
{
    /// <summary>
    /// Interaction logic for SetNameDialog.xaml
    /// </summary>
    public partial class SetNameDialog
    {
        public SetNameDialog()
        {
            InitializeComponent();

        }

        private void ButtonBase_Onclick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
