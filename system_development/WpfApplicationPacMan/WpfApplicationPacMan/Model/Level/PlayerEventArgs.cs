using System;

namespace WpfApplicationPacMan.Model.Level
{
    sealed class PlayerEventArgs : EventArgs
    {
        public int Score
        {
            get;
            set;
        }
    }
}
