using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApplicationPacMan.Model.Ghosts
{
    class PositionsEventArgs : EventArgs
    {
        public List<Position> Positions
        {
            get;
            set;
        }

        public bool IsAttackedModeOn
        {
            get;
            set;
        }
    }
}
