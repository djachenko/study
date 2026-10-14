using System;
using PacMan.Model;

namespace PacMan.Helpers
{
    public sealed class MoveEventArgs : EventArgs
    {
        public Direction Direction { get; set; }
    }
}
