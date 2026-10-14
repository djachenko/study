using System;
using Gui.Models;

namespace Gui.ViewModels {
    internal sealed class KeybindingsGroupViewModel {
        public event EventHandler IsChangingChanged;
        private bool _isChanging;
        public KeybindingsGroup  KeybindingsGroup { get; }

        public bool IsChanging {
            get { return _isChanging; }
            set {
                _isChanging = value;
                IsChangingChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        public KeybindingsGroupViewModel(KeybindingsGroup kbGroup) {
            if (kbGroup == null) {
                throw new ArgumentException("kbGroup can't be null");
            }
            KeybindingsGroup = kbGroup;
        }
    }
}