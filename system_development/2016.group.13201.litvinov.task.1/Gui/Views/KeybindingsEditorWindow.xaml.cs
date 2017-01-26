using System.Windows.Input;
using Gui.ViewModels;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для KeybindingsEditor.xaml
    /// </summary>
    internal sealed partial class KeybindingsEditor {
        public KeybindingsEditor() {
            InitializeComponent();
        }

        private void KeybindingsEditor_OnKeyDown(object sender, KeyEventArgs e) { 
            var dc = (KeybindingsEditorWindowViewModel) DataContext;
            foreach (KeybindingViewModel kvm in dc.KeybindingViewModels) {
                kvm.TrySetKey(e.Key);
            }
        }
    }
}
