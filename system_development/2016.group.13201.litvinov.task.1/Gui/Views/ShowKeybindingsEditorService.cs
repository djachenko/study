using System.Windows;
using Gui.ViewModels;

namespace Gui.Views {
    internal sealed class ShowKeybindingsEditorService : IShowKeybindingsEditorService{
        public void ShowKeybindingsEditor(KeybindingsEditorWindowViewModel viewModel) {
            var win = new KeybindingsEditor {
                DataContext = viewModel,
                Owner = Application.Current.MainWindow
            };
            win.Show();
        }
    }
}
