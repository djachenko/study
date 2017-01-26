using Gui.ViewModels;
using System.Windows;

namespace Gui.Views {
    sealed class AskNameService : IAskNameService {
        private string _result;
        private void OpenDlg() {
            var w = new StringInputWindow("Имя", "Вы -- один из лучших игроков. Введите имя.") {
                Owner = Application.Current.MainWindow
            };
            w.ShowDialog();
            _result = w.Result;
        }

        public string AskName() {
            Application.Current.Dispatcher.Invoke(OpenDlg);
 
            return _result;
        }
    }
}
