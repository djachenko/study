using System;
using System.Windows.Input;

namespace Gui.Models {
    internal sealed class Keybinding {
        public event EventHandler OnChanged;

        private string _name;
        public string Name {
            get { return _name; }
            set {
                if (value == null) {
                    throw new ArgumentException("name can't be null");
                }
                _name = value;
                OnChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        private Key _keyname;

        public Key Keyname {
            get {
                return _keyname;
            }
            set {
                _keyname = value;
                OnChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        public Keybinding(string name, Key keyname) {
            _name = name;
            _keyname = keyname;
        }
    }
}
