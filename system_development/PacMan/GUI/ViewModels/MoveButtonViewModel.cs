using PacMan.Annotations;
using PacMan.Model;

namespace GUI.ViewModels
{
    public sealed class MoveButtonViewModel
    {
        public string Name { get; set; }
        [UsedImplicitly]
        public int Index { get; set; }
        internal Game Origin { get; set; }
        internal Direction Direction { get; set; }
    }
}
