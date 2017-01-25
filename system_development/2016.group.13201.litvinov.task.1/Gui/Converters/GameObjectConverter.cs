using System;
using System.Collections.Generic;
using System.Windows.Data;
using System.Globalization;

namespace Gui.Converters {
    internal sealed class GameObjectConverter : IValueConverter {

        private static readonly Dictionary<string, string> ObjectNameToIcon =
            new Dictionary<string, string>();

        private static void AddEntry(string name, string resourceImage) {
            if (name == null || resourceImage == null) {
                return;
            }
            ObjectNameToIcon.Add(name, $"pack://application:,,,/Resources/{resourceImage}");
        }
       
        static GameObjectConverter() {
            AddEntry("none", "none.png");
            AddEntry("wall", "wall.png");
            AddEntry("dot", "dot.png");
            AddEntry("energizer", "energizer.png");
            AddEntry("fruit", "fruit.png");
            AddEntry("pacman", "pacman.png");
            foreach (var gname in new List<string>{ "ghost_a", "ghost_b", "ghost_c"}) {
                AddEntry(gname, "ghost_normal.png");
            }
            foreach (var gname in new List<string> { "ghost_a_p", "ghost_b_p", "ghost_c_p" }) {
                AddEntry(gname, "ghost_pursuit.png");
            }
        }

        private static GameObjectConverter _instance;
        public static GameObjectConverter Instance {
            get {
                return _instance = _instance ?? new GameObjectConverter();
            }
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            var objectName = value as string;
            if (objectName != null) {
                if (!ObjectNameToIcon.ContainsKey(objectName)) {
                    return ObjectNameToIcon["none"];
                }
                return ObjectNameToIcon[objectName];
            }
            return ObjectNameToIcon["none"];
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            throw new NotImplementedException();
        }
    }
}
