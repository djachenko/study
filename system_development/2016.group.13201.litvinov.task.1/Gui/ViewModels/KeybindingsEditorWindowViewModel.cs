using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using Gui.Models;

namespace Gui.ViewModels {
    internal sealed class KeybindingsEditorWindowViewModel : INotifyPropertyChanged {
        private ObservableCollection<KeybindingViewModel> _keybindingViewModels;

        public ObservableCollection<KeybindingViewModel> KeybindingViewModels {
            get { return _keybindingViewModels; }
            set {
                _keybindingViewModels = value;
                OnPropertyChanged(nameof(KeybindingViewModels));
            }
        }

        public KeybindingsEditorWindowViewModel(KeybindingsGroup keybindingsGroup) {
            if (keybindingsGroup == null) {
                throw new ArgumentException("keybindingsGroup can't be null");
            }
            var keybindingViewModels = new ObservableCollection<KeybindingViewModel>();
            var keybindingsGroupViewModel = new KeybindingsGroupViewModel(keybindingsGroup);
            foreach (var kb in keybindingsGroup.All) {
                keybindingViewModels.Add(new KeybindingViewModel(kb, keybindingsGroupViewModel));
            }
            KeybindingViewModels = keybindingViewModels;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
