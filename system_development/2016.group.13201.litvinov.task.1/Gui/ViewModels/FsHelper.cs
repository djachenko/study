using System;
using System.IO;

namespace Gui.ViewModels {
    internal static class FsHelper {
        public static string GetPathInAppdata(string filename) {
            string settingsDirectory = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            if (!Directory.Exists(settingsDirectory)) {
                Directory.CreateDirectory(settingsDirectory);
            }

            return Path.Combine(settingsDirectory, filename);
        }
    }
}
