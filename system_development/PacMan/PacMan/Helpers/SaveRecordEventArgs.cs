using System;

namespace PacMan.Helpers
{
    public sealed class SaveRecordEventArgs : EventArgs
    {
        public int Score { get; set; }
    }
}
