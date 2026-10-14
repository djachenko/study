using System;
using System.Runtime.InteropServices;

namespace GameCore {
    [ComVisible(false)] // cuz warning
    public sealed class Field<T> {
        private readonly T[,] _field;
        public int Width { get; }
        public int Height { get; }

        internal Field(int width, int height) {
            if (width <= 0 || height <= 0) {
                throw new ArgumentException("field's width or height must be positive");
            }
            Width = width;
            Height = height;
            _field = new T[width, height];
        }

        private bool IsBoundsOkX(int x) {
            return x >= 0 && x < Width;
        }

        private bool IsBoundsOkY(int y) {
             return y >= 0 && y < Height;
        }

        internal bool IsBoundsOk(int x, int y) {
            return IsBoundsOkX(x) && IsBoundsOkY(y);
        }

        private void CheckBounds(int x, int y) {
            if (!IsBoundsOkX(x)) {
                throw new ArgumentOutOfRangeException(nameof(x));
            }
            if (!IsBoundsOkY(y)) {
                throw new ArgumentOutOfRangeException(nameof(y));
            }
        }

        private T Get(int x, int y) {
            CheckBounds(x,y);
            return _field[x, y];
        }

        private void Set(int x, int y, T value) {
            CheckBounds(x,y);
            _field[x, y] = value;
        }

        internal T this[PointInt point] {
            get {              
                return Get(point.X, point.Y);
            }
            set {
                Set(point.X, point.Y, value);
            }
        }

        public T this[int x, int y] {
            get { 
                return Get(x, y);
            }
            internal set {
                Set(x, y, value);
            }
        }

        internal void Foreach(Action<int, int, T> traverseFunction) {
            for (int i = 0; i < Width; ++i) {
                for (int j = 0; j < Height; ++j) {
                    traverseFunction?.Invoke(i, j, this[i, j]);
                }
            }
        }
    }
}
