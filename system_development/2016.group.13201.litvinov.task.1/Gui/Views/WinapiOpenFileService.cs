using Gui.ViewModels;
using Microsoft.Win32;

namespace Gui.Views {
    internal sealed class WinapiOpenFileService : IOpenFileService{
        public string GetFileName() {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            return openFileDialog.ShowDialog() == true ? openFileDialog.FileName : null;
        }
    }
}
