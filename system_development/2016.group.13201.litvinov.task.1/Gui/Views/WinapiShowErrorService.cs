using System.Windows;
using Gui.ViewModels;

namespace Gui.Views {
    internal sealed class WinapiShowErrorService : IShowErrorService {
        public void ShowError(string msg) {
            MessageBox.Show(msg, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }
}
