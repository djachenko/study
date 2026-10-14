using System;

namespace GameCore {
    internal sealed class TickTimer {
        private readonly Action _callback;
        private readonly int _maxValue;
        private int _timer;

        public TickTimer(int maxValue, Action callback) {
            if (maxValue <= 0) {
                throw new ArgumentException("maxValue must be positive", nameof(maxValue));
            }
            _callback = callback;
            _maxValue = maxValue;
            Stop();
        }

        public void Start() {
            _timer = 0;
        }

        private void Stop() {
            _timer = _maxValue + 1;
        }

        public void Tick() {
            if (_timer == _maxValue) {
                _callback();
            } else if (_timer < _maxValue) {
                _timer++;
            }
        }
    }
}
