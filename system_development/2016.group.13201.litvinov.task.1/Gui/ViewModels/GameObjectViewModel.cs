using System;
using System.ComponentModel;
using GameCore;

namespace Gui.ViewModels {
    internal sealed class GameObjectViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;
        private readonly GameObject _gameObject;

        public double XPos => _gameObject.Position.X;
        public double YPos => _gameObject.Position.Y;

        public PointInt Direction => _gameObject.Direction;
        public string ObjectName => _gameObject.Name;

        public GameObjectViewModel(GameObject gameObject) {
            if (gameObject == null) {
                throw new ArgumentException("gameObject can't be null");
            }
            _gameObject = gameObject;
            _gameObject.PositionChanged += (sender, args) => {
                OnPropertyChanged(nameof(XPos));
                OnPropertyChanged(nameof(YPos));
                OnPropertyChanged(nameof(Direction));
            };
            _gameObject.NameChanged += (sender,args) => OnPropertyChanged(nameof(ObjectName));
        }

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
