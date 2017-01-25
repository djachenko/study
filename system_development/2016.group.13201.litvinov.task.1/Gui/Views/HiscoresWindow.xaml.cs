using System.Windows.Input;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для HiscoresWindow.xaml
    /// </summary>
    internal sealed partial class HiscoresWindow {
        public HiscoresWindow() {
            InitializeComponent();
        }

        private void HiscoresWindow_OnPreviewKeyDown(object sender, KeyEventArgs e) {
            if (e.Key == Key.Escape) {
                Close();
            }
        }
    }
}
