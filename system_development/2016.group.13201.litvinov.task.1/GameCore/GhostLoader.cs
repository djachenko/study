using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace GameCore {
    sealed class GhostLoader {
        private readonly List<Type> _ghostTypes;
        private int _createIdx;

        private static readonly HashSet<string> AcceptedPkTokens = new HashSet<string> {
            "b885454193188bb8",
            "049b005a851a0de5",
            "4b1cef1f0619de60"
        };

        private static string GetPkToken(Assembly assembly) {
            if (assembly == null) {
                throw new ArgumentException("assembly can't be null", nameof(assembly));
            }
            byte[] publicKeyTokenBytes = assembly.GetName().GetPublicKeyToken();
            return String.Concat(publicKeyTokenBytes.Select(i => i.ToString("x2")));
        }

        public GhostLoader() {
            string ghostsDir = Path.Combine(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location));
            _ghostTypes = new List<Type>();
            
            foreach (var dllFileName in Directory.GetFiles(ghostsDir, "*.dll")) {
                Assembly assembly;
                try {
                    assembly = Assembly.LoadFile(dllFileName);
                } catch (FileLoadException) {
                    throw new GhostsLoadException("Нарушена целостность сборки с приведением");
                }
                if (!AcceptedPkTokens.Contains(GetPkToken(assembly))) {
                    continue;
                }
                foreach (var exportedType in assembly.GetExportedTypes()) {
                    if (exportedType.IsSubclassOf(typeof(Ghost)) && exportedType.IsSealed) {
                        _ghostTypes.Add(exportedType);
                    }
                }
            }
            
            
            if (_ghostTypes.Count == 0) {
                throw new GhostsLoadException("Не обнаружено подходящих сборок с приведениями");
            }
            _createIdx = 0;
        }

        public Ghost CreateGhost(Field<GameObject> staticGameObjects, PointInt initialPosition) {
            // this is wrapper so argument exceptions will throw in inner calls
            var ghost = Activator.CreateInstance(_ghostTypes[_createIdx], staticGameObjects, initialPosition);
            _createIdx = (_createIdx + 1) % _ghostTypes.Count;
            return (Ghost)ghost;
        }
    }
}
