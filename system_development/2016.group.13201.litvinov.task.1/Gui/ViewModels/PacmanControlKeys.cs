using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Input;
using Gui.Models;

namespace Gui.ViewModels {
    internal sealed class PacmanControlKeys : INotifyPropertyChanged, IKeybindingsSource {
        private readonly Keybinding _moveLeftKb, _moveRightKb, _moveUpKb, _moveDownKb;
        private readonly List<Keybinding> _keybindings;
        
        public Key MoveLeftKey => _moveLeftKb.Keyname;
        public Key MoveRightKey => _moveRightKb.Keyname;
        public Key MoveUpKey => _moveUpKb.Keyname;
        public Key MoveDownKey => _moveDownKb.Keyname;

        public PacmanControlKeys() {
            _moveLeftKb = new Keybinding("Go left", Key.Left);
            _moveRightKb = new Keybinding("Go right", Key.Right);
            _moveUpKb = new Keybinding("Go up", Key.Up);
            _moveDownKb = new Keybinding("Go down", Key.Down);
            _keybindings = new List<Keybinding> {_moveLeftKb, _moveRightKb, _moveUpKb, _moveDownKb};
            
            _moveLeftKb.OnChanged += (sender, args) => OnPropertyChanged(nameof(MoveLeftKey));
            _moveRightKb.OnChanged += (sender, args) => OnPropertyChanged(nameof(MoveRightKey));
            _moveUpKb.OnChanged += (sender, args) => OnPropertyChanged(nameof(MoveUpKey));
            _moveDownKb.OnChanged += (sender, args) => OnPropertyChanged(nameof(MoveDownKey));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public List<Keybinding> GetKeybindings() {
            return _keybindings;
        }
    }
}
