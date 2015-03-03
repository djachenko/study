using System.Windows;
using PacMan.Model;

namespace GUI.Views
{
    public sealed partial class RecordTableDialog
    {
        public RecordTableDialog()
        {
            InitializeComponent();

            DataContext = RecordTable.Instance;
        }

        private void OnOkButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
