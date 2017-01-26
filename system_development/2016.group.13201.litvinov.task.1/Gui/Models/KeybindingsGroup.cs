using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;

namespace Gui.Models {
    internal sealed class KeybindingsGroup {
        public List<Keybinding> All { get; }

        public bool IsUnbound(Key k) {
            return All.All(keybinding => keybinding.Keyname != k);
        }

        public KeybindingsGroup() {
            All = new List<Keybinding>();
        }
    }
}
