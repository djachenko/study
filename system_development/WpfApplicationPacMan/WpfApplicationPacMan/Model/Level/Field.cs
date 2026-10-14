using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.ComponentModel;
using System.IO;
using WpfApplicationPacMan.Annotations;
using WpfApplicationPacMan.Properties;

namespace WpfApplicationPacMan.Model.Level
{
    public sealed class Field : INotifyPropertyChanged
    {

        #region fields
        private readonly String[] _map;
        private List<Position> _wallList = new List<Position>();
        private List<Position> _pillList = new List<Position>();
        private readonly List<Position> _ghostList = new List<Position>();
        private List<Position> _powerPillList = new List<Position>();
        private int _heightOfField;
        private int _widthOfField;
        private Position _objectPosition;
        private Position _playerStartPosition;
        private Player.Direction _objectDirection;

        #endregion fields

        #region properties

        public List<Position> WallsPositions
        {
            get
            {
                return _wallList;
            }
            set
            {
                _wallList = value;
                OnPropertyChanged();
            }
        }
        public List<Position> PillsPositions
        {
            get
            {
                return _pillList;
            }
            set
            {
                _pillList = value;
                OnPropertyChanged();
            }
        }
        public List<Position> PowerPillsPositions
        {
            get
            {
                return _powerPillList;
            }
            set
            {
                _powerPillList = value;
                OnPropertyChanged();
            }
        }
        public Position PlayerStartPosition
        {
            get
            {
                InitPlayerStartPosition();
                return _playerStartPosition;
            }
        }
        public List<Position> GhostRespawnPositions
        {
            get
            {
                return _ghostList;
            }
        }
        public int HeightOfField
        {
            get
            {
                return _heightOfField;
            }
            private set
            {
                _heightOfField = value;
                OnPropertyChanged();
            }
        }
        public int WidthOfField
        {
            get
            {
                return _widthOfField;
            }
            private set
            {
                _widthOfField = value;
                OnPropertyChanged();
            }
        }

        #endregion
        
        /// <summary>
        ///открыть файл с картой и инициализировать _map значениями из файла
        /// </summary>
        /// <param name="path"> путь до файла с картой</param>
        public Field(String path)
        {
            try
            {
                using (var sr = new StreamReader(path))
                {
                    var firstline = sr.ReadLine();
                    if (firstline != null)
                    {
                        var s = firstline.Split(' ');
                        if (s[1] != null)
                        {
                            _map = new string[int.Parse(s[1])];
                        }
                    }
                    firstline = sr.ReadToEnd();
                    _map = firstline.Split('\n');
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(Resources.Field_Field_The_file_could_not_be_read_);
                Console.WriteLine(e.Message);
            }

            HeightOfField = _map.Length;
            WidthOfField=_map[0].Length - 1;

            //для инициализации начального поля
            InitPlayerStartPosition();
            InitPositions('.');
            InitPositions('#');
            InitPositions('=');
            InitPositions('*');
        }

        /// <summary>
        /// поиск заданного символов на карте и установка их позиций
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns></returns>
        private void InitPositions(char symbol)
        {
            var i = 0;
            foreach (var s in _map)
            {
                for (var j = 0; j < s.Length; j++)
                {
                    if (s[j] != symbol) continue;
                    switch (symbol)
                    {
                        case '.':
                            _pillList.Add(new Position { CoordinateX = j, CoordinateY = i });
                            break;
                        case '#':
                            _wallList.Add(new Position { CoordinateX = j, CoordinateY = i });
                            break;
                        case '=':
                            _ghostList.Add(new Position { CoordinateX = j, CoordinateY = i });
                            break;
                        case '*':
                            _powerPillList.Add(new Position { CoordinateX = j, CoordinateY = i });
                            break;
                    }
                }
                i++;
            }

            switch (symbol)
            {
                case '.':
                    return;
                case '=':
                    return;
                case '*':
                    return;
                default:
                    return;
            }
        }

        /// <summary>
        /// устанавливает начальную позицию пакмэна на карте
        /// </summary>
        /// <returns></returns>
        private void InitPlayerStartPosition()
        {
            var i = 0;
            var j = 0;
            foreach (var s in _map)
            {
                j = s.IndexOf('/');
                if (j != -1)
                {
                    break;
                }
                i++;
            }
            _playerStartPosition = new Position { CoordinateX = j, CoordinateY = i };
        }


        public bool IsTheWayFree(Position playerPosition, Player.Direction direction)
        {
            if (playerPosition == null)
            {
                throw new ArgumentNullException("playerPosition");
            }

            _objectDirection = direction;
            _objectPosition = playerPosition;

            return WallsPositions.FindIndex(FindBarrier) == -1;
        }

        /// <summary>
        /// используется в качестве предиката
        /// находит стену в которую объект врежется, если будет двигаться в заданную сторону
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        private bool FindBarrier(Position obj)
        {
            switch (_objectDirection)
            {
                case Player.Direction.Up:
                    return obj.CoordinateX == _objectPosition.CoordinateX && obj.CoordinateY == _objectPosition.CoordinateY - 1;
                case Player.Direction.Down:
                    return obj.CoordinateX == _objectPosition.CoordinateX && obj.CoordinateY == _objectPosition.CoordinateY + 1;
                case Player.Direction.Left:
                    return obj.CoordinateX == _objectPosition.CoordinateX - 1 && obj.CoordinateY == _objectPosition.CoordinateY;
                case Player.Direction.Right:
                    return obj.CoordinateX == _objectPosition.CoordinateX + 1 && obj.CoordinateY == _objectPosition.CoordinateY;
                default:
                    return true;
            }
        }


        /// <summary>
        ///конвертируем _map to 1,-1 для передачи ее призракам для поиска пути 
        /// </summary>
        /// <returns></returns>
        public int[,] GetMatrix()
        {
            var matrix = new int[HeightOfField,WidthOfField];
            for (var i = 0; i < HeightOfField; i++)
            {
                for (var j = 0; j < WidthOfField; j++)
                {
                    switch (_map[i][j])
                    {
                        case '#':
                            matrix[i,j] = (int) Matrix.Wall;
                            break;
                        default:
                            matrix[i, j] = (int) Matrix.Space;
                            break;
                    }
                }
            }
            return matrix;
        }

        public int GetNumberOfGhosts()
        {
            return _ghostList.Count;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
