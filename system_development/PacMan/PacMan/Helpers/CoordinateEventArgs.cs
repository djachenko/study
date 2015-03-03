using System;
using PacMan.Model.Cells;

namespace PacMan.Helpers
{
    public sealed class CoordinateEventArgs : EventArgs
    {
        public Cell CellRemoved { get; internal set; }
        public Cell CellAdded { get; internal set; }
    }
}
