using System;
using System.ComponentModel;
using System.Windows.Input;
using Gui.Models;

namespace Gui.ViewModels {
    internal sealed class KeybindingViewModel : INotifyPropertyChanged {
        private readonly Keybinding _keybinding;
        private readonly KeybindingsGroupViewModel _kbGroupViewModel;

        public string KeybindingName {
            get { return _keybinding.Name; }
            set {
                _keybinding.Name = value; 
                OnPropertyChanged(nameof(KeybindingName));
            }
        }

        public string Keyname => _isChanging ? "<Press key>" : _keybinding.Keyname.ToString();
        public event Action ChangeErrorEvent;
        public event Action ChangeSuccessEvent;

        private void SetKeyname(Key k) {
            _keybinding.Keyname = k;
            OnPropertyChanged(nameof(Keyname));
        }

        private bool _isChanging;

        private bool IsChanging {
            get { return _isChanging; }
            set {
                _isChanging = value;
                _kbGroupViewModel.IsChanging = value;
                OnPropertyChanged(nameof(Keyname));
                OnPropertyChanged(nameof(IsChanging));
            }
        }

        private sealed class ChangeCommandHelper : ICommand {
            private readonly KeybindingViewModel _keybindingViewModel;
            public bool CanExecute(object parameter) {
                return !_keybindingViewModel._kbGroupViewModel.IsChanging;
            }

            public void Execute(object parameter) {
                _keybindingViewModel.IsChanging = true;
            }

            public event EventHandler CanExecuteChanged;

            public ChangeCommandHelper(KeybindingViewModel keybindingViewModel) {
                if (keybindingViewModel == null) {
                    throw new ArgumentException("keybindingViewModel can't be null");
                }
                _keybindingViewModel = keybindingViewModel;
                _keybindingViewModel._kbGroupViewModel.IsChangingChanged += 
                    (sender, args) => CanExecuteChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        public ICommand ChangeCommand { get; }

        public KeybindingViewModel(Keybinding keybinding, KeybindingsGroupViewModel kbGroupViewModel) {
            if (keybinding == null) {
                throw new ArgumentException("keybinding can't be null");
            }
            if (kbGroupViewModel == null) {
                throw new ArgumentException("kbGroupViewModel can't be null");
            }
            _keybinding = keybinding;
            _kbGroupViewModel = kbGroupViewModel;
            ChangeCommand = new ChangeCommandHelper(this);
        }

        public void TrySetKey(Key k) {
            if (IsChanging) {
                if (k == _keybinding.Keyname || _kbGroupViewModel.KeybindingsGroup.IsUnbound(k)) {
                    SetKeyname(k);
                    IsChanging = false;
                    ChangeSuccessEvent?.Invoke();
                }
                else {
                    ChangeErrorEvent?.Invoke();
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
