using System;
using System.IO;
using System.Windows.Forms;
using WpfApplicationPacMan.Model.Ghosts;

namespace WpfApplicationPacMan.Model.Level
{
    class LevelsLoader
    {
        private static readonly string RootDir = Directory.GetCurrentDirectory();
        private readonly Player _player;
        private int _currentLevelNumber;
        private readonly GhostsFactory _ghostsFactory;
        private readonly EventHandler _ghostsChangesPositionsEventHandler;
        private readonly EventHandler _pillsChangesEventHandler;
        private readonly EventHandler _powerPillsEventHandler;

        private readonly String[] _pathToMaps = new string[5];



        public LevelsLoader(Player player, EventHandler ghostsEventHandler, EventHandler eventHandler, EventHandler powerPillsEventHandler)
        {
            var mapsDir = Application.StartupPath + @"..\..\..\Resources\Maps\";
            var i = 0;
            foreach (var fileName in Directory.GetFiles(mapsDir, "*.txt"))
            {
                _pathToMaps[i] = fileName;
                i++;
            }

            _ghostsFactory = new GhostsFactory(RootDir);
            _player = player;
            _ghostsChangesPositionsEventHandler = ghostsEventHandler;
            _pillsChangesEventHandler = eventHandler;
            _powerPillsEventHandler = powerPillsEventHandler;
        }

        public Level GetNextLevel()
        {
            _currentLevelNumber++;
            var level = _currentLevelNumber >= 4 ? null : new Level(_currentLevelNumber, _pathToMaps[_currentLevelNumber - 1], _player, _ghostsFactory);
            if (level == null)
            {
                return null;
            }
            level.ChangesHandler += _ghostsChangesPositionsEventHandler;
            level.PillsChangesHandler += _pillsChangesEventHandler;
            level.PowerPillsChangesHandler += _powerPillsEventHandler;
            return level;
        }
    }
}
