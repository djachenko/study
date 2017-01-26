using System.Windows;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для StringInputWindow.xaml
    /// </summary>
    internal sealed partial class StringInputWindow {
        internal StringInputWindow(string title, string description) {
            InitializeComponent();            
            Title = title;
            Description.Text = description;
        }

        public string Result { get; private set; }

        private void Ok_Click(object sender, RoutedEventArgs e) {
            Result = UserInput.Text;
            Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e) {
            Close();
        }
    }
}
