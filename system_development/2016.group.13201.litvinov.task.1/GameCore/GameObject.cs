using System;

namespace GameCore {
    public abstract class GameObject {
        private string _name;
        public event EventHandler PositionChanged;
        public event EventHandler NameChanged;
        internal abstract bool IsPassable { get; }

        public string Name {
            get { return _name; }
            protected set {
                if (value == null) {
                    throw new ArgumentException("name can't be null");
                }
                _name = value;
                NameChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        public abstract PointDouble Position { get; }
        public abstract PointInt Direction { get; }
        internal abstract void InteractWith(GameObject cause);

        protected void OnPositionChanged() {
            PositionChanged?.Invoke(this, EventArgs.Empty);
        }
    }
}
