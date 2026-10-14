using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using WpfApplicationPacMan.View;

namespace WpfApplicationPacMan.Model.Ghosts
{
    class GhostsFactory
    {
        private int _counter;
        private readonly List<Type> _loadedFiles = new List<Type>();

        public GhostsFactory(string path)
        {
            try
            {
                foreach (var fileName in Directory.GetFiles(path, "*.dll"))
                {
                    if (!String.IsNullOrEmpty(fileName))
                    {
                        if (Verify(fileName))
                        {
                            LoadAI(fileName);
                        }
                    }
                }

                if (_loadedFiles.Count == 0)
                {
                    var ghostsNotFound = new GhostsNotFound();
                    ghostsNotFound.ShowDialog();
                    throw new GhostsNotFoundException();
                }
            }
            catch (DirectoryNotFoundException)
            {
                throw new Exception("can't load files");
            }
            catch (GhostsNotFoundException)
            {
                throw new Exception("No one ghost not found!");
            }
        }

        private void LoadAI(string fileName)
        {

            if (null == fileName)
            {
                throw new ArgumentNullException("");
            }


            foreach (var variable in Assembly.LoadFile(fileName).GetTypes())
            {
                _loadedFiles.Add(variable);
            }
        }

        //<summary>
        //создает призрака с конретным поведением
        //</summary>
        public Ghost GetGhost(Position position, int[,] matrix)
        {
            if (position == null)
            {
                throw new ArgumentNullException("position");
            }
            if (matrix == null)
            {
                throw new ArgumentNullException("matrix");
            }


            return new Ghost(GetNextAI(), position, matrix);
        }

        private GhostAI GetNextAI()
        {
            _counter++;
            _counter %= _loadedFiles.Count;
            var type = _loadedFiles[_counter];
            return (GhostAI) Activator.CreateInstance(type);
        }


        [DllImport("mscoree.dll", CharSet = CharSet.Unicode)]
        private static extern bool StrongNameSignatureVerificationEx(
            [MarshalAs(UnmanagedType.LPWStr)] string wszFilePath,
            [MarshalAs(UnmanagedType.U1)] bool fForceVerification,
            [MarshalAs(UnmanagedType.U1)] out bool pfWasVerified);

        private static bool Verify(String path)
        {
            bool result;
            return StrongNameSignatureVerificationEx(path, true, out result);
        }

    }
}
