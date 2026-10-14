using System;
using System.Timers;

namespace WpfApplicationPacMan.Model
{
    sealed class Ticker : IDisposable
    {
        private const int MillisecondsOfDelay = 300;
        private readonly Timer _timer;
        private readonly Action _onTickAction;

        public Ticker(Action onTickAction)
        {
            _onTickAction = onTickAction;
            _timer = new Timer(MillisecondsOfDelay);
            _timer.Elapsed += Tick;

        }

        private void Tick(object sender, ElapsedEventArgs e)
        {
            _onTickAction();
        }

        public void Dispose()
        {
            _timer.Dispose();
        }

        public void Start()
        {
            _timer.Start();
        }

        public void Stop()
        {
            _timer.Stop();
        }
    }
}
