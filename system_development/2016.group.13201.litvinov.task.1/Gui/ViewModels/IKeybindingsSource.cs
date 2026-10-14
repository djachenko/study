using System.Collections.Generic;
using Gui.Models;

namespace Gui.ViewModels {
    internal interface IKeybindingsSource {
        List<Keybinding> GetKeybindings();
    }
}
