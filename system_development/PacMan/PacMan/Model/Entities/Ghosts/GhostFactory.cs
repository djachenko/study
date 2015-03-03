using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using PacMan.Model.Exceptions;
using PacMan.Properties;

namespace PacMan.Model.Entities.Ghosts
{
    sealed class GhostFactory
    {
        private static readonly Lazy<GhostFactory> Lazy = new Lazy<GhostFactory>(() => new GhostFactory());
        
        private List<Type> Ghosts { get; set; }
        private int NextGhostIndex { get; set; }

        internal static GhostFactory Instance
        {
            get { return Lazy.Value; }
        }

        private GhostFactory()
        {
            NextGhostIndex = 0;

            Init();
        }

        private void Init()
        {
            try
            {
                var dllPath = Resources.ResourcePath + Resources.GhostsFolder;
                var files = Directory.GetFiles(dllPath, "*.dll");

                var ais = (from fileName in files
                    select Path.GetFullPath(fileName)
                    into fullPath
                    select Assembly.LoadFile(fullPath)
                    into assembly
                    from type in assembly.GetExportedTypes()
                    where type.IsSubclassOf(typeof (Ghost))
                    select type).ToList();

                Ghosts = ais;
            }
            catch (Exception e)
            {
                throw new GhostsNotValidException("Unable to load ghosts' dlls", e);
            }
            
        }

        internal Ghost GetNextGhost(Field field, int x, int y)
        {
            var ghost = Activator.CreateInstance(Ghosts[NextGhostIndex], field, x, y) as Ghost;
            
            NextGhostIndex = (NextGhostIndex + 1) % Ghosts.Count;
            
            return ghost;
        }
    }
}
