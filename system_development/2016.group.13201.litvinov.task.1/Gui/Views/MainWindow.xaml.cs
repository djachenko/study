using System.Windows;
using Gui.ViewModels;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    internal sealed partial class MainWindow {
        public MainWindow() {
            InitializeComponent();
            
            var dc = (MainWindowViewModel)DataContext;
            dc.OpenFileService = new WinapiOpenFileService();
            dc.ShowErrorService = new WinapiShowErrorService();
            dc.ShowKeybindingsEditorService = new ShowKeybindingsEditorService();
            dc.ShowHiscoresService = new ShowHiscoresService();
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e) {
            var dc = (MainWindowViewModel)DataContext;
            dc.StartEmbeddedCampaign.Execute(null);
        }
    }
}
