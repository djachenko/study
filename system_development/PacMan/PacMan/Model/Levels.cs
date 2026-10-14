using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using PacMan.Properties;

namespace PacMan.Model
{
    sealed class Levels
    {
        private static readonly Lazy<Levels> Lazy = new Lazy<Levels>(() => new Levels());

        public static Levels Instance
        {
            get { return Lazy.Value; }
        }

        internal IEnumerable<string> AvailableLevels { get; private set; }
        private Dictionary<string, string> LevelsData { get; set; }

        private Levels()
        {
            LevelsData = new Dictionary<string, string>();

            ReadConfig();
        }

        private void ReadConfig()
        {
            var configPath = Resources.ResourcePath + Resources.ConfigFileName;

            using (var reader = File.OpenText(configPath))
            {
                var line = reader.ReadLine();

                var filenames = new List<string>();

                while (line != null)
                {
                    filenames.Add(line);

                    line = reader.ReadLine();
                }

                AvailableLevels = filenames;
            }
        }

        private TextReader GetLevel(string fileName)
        {
            if (!AvailableLevels.Contains(fileName))
            {
                return null;
            }

            if (!LevelsData.ContainsKey(fileName))
            {
                LoadLevel(fileName);
            }

            return new StringReader(LevelsData[fileName]);
        }

        internal TextReader GetLevel(int index)
        {
            if (AvailableLevels.Count() < index)
            {
                return null;
            }

            var fileName = AvailableLevels.Take(index).Last();

            return GetLevel(fileName);
        }

        private void LoadLevel(string fileName)
        {
            var path = Resources.ResourcePath + fileName;

            using (var reader = File.OpenText(path))
            {
                var levelData = reader.ReadToEnd();

                LevelsData[fileName] = levelData;
            }
        }
    }
}
