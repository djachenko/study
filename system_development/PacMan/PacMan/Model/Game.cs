using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Timers;
using PacMan.Helpers;
using PacMan.Model.Cells;
using PacMan.Model.Entities;
using PacMan.Model.Entities.Ghosts;
using PacMan.Properties;

namespace PacMan.Model
{
    public sealed class Game : IDisposable
    {
        internal const int TimerInterval = 100;
        private const int InitialPlayerLives = 2;

		private int _pillCount;
        private Field _field;
        private int _playerLives;
        private int _levelNumber;
        private int _levelPoints;

        private int _previousLevelPoints;

        public Field Field
        {
            get { return _field; }
            private set
            {
                _field = value;

                FieldReseted.Raise(this);
            }
        }

        private Player Player { get; set; }

        private List<Ghost> Ghosts { get; set; }

        private Timer Timer { get; set; }

        private int PillCount
		{
			get { return _pillCount; }
			set
			{
			    _pillCount = value;

                if (_pillCount == 0)
				{
					LevelFinished = true;
				}
			}
		}

        private int IterationCount { get; set; }

        public bool Started
        {
            get { return Timer.Enabled; }
            private set
            {
                Timer.Enabled = value;

                StateChanged.Raise(this);
            }
        }

        public int LevelNumber
        {
            get { return _levelNumber; }
            private set
            {
                _levelNumber = value;

                LevelChanged.Raise(this);
            }
        }

        private int PreviousLevelPoints
        {
            get { return _previousLevelPoints; }
            set
            {
                _previousLevelPoints = value; 
                
                PointsChanged.Raise(this);
            }
        }

        public int CampaignPoints
        {
            get { return PreviousLevelPoints + LevelPoints; }
        }

        public int LevelPoints
        {
            get { return _levelPoints; }
            private set
            {
                _levelPoints = value;
                
                PointsChanged.Raise(this);
            }
        }

        public int PlayerLives
        {
            get { return _playerLives; }
            private set
            {
                _playerLives = value;

                PlayerLivesChanged.Raise(this);

                if (_playerLives == 0)
                {
                    GameFinished = true;
                }
            }
        }

        private bool LevelFinished { get; set; }
        private bool GameFinished { get; set; }

        public Direction PlayerDirection { get; set; }

        public event EventHandler StateChanged;
        public event EventHandler FieldReseted;
        public event EventHandler PointsChanged;
        public event EventHandler PlayerLivesChanged;
        public event EventHandler<SaveRecordEventArgs> PlayerDied;
        public event EventHandler LevelChanged;

        public Game()
		{
            Timer = new Timer(TimerInterval);
            Timer.Elapsed += (sender, args) =>
            {
                Tick();
            };

            Field = new Field();
            Ghosts = new List<Ghost>();

            ResetCampaign();
		}

        void ResetCampaign()
        {
            PreviousLevelPoints = 0;
            PlayerLives = InitialPlayerLives;
            LevelNumber = 1;

            GameFinished = false;

            ResetLevel();
        }

        void ResetLevel()
        {
            Stop();

            _pillCount = 0;

            using (var reader = Levels.Instance.GetLevel(LevelNumber))
            {
                Field.Init(reader);
            }
            
            Ghosts.Clear();

            Init();

            FieldReseted.Raise(this);

            IterationCount = 0;
            LevelPoints = 0;

            LevelFinished = false;
        }

		void Init()
		{
			try
			{
				using (var reader = Levels.Instance.GetLevel(LevelNumber))
				{
					var sizesLine = reader.ReadLine() ?? "0 0";
					var sizes = sizesLine.Split(' ');

					var width = int.Parse(sizes[0]);
					var height = int.Parse(sizes[1]);

				    var ghostFactory = GhostFactory.Instance;

					for (var y = 0; y < height; y++)
					{
						for (var x = 0; x < width; x++)
						{
							var c = reader.Read();
							GameEntity currentEntity;

							switch (c)
							{
								case CellRepresentations.PillCellRepresentation:
                                    var pill = new Pill(Field, x, y);

                                    pill.Eaten += (sender, args) =>
							        {
							            LevelPoints++;
							            PillCount--;
							        };

							        PillCount++;

							        currentEntity = pill;
									break;
                                case CellRepresentations.PlayerCellRepresentation:
									Player = new Player(Field, x, y);

							        var owned = Field[x, y];
							        Player.OnHighStateChanged += (sender, args) => owned.OnRepresentationChanged();
							        Player.WasHit += (sender, args) => PlayerLives--;
                                    Player.ResetAll += (sender, args) => ResetEntities();

                                    currentEntity = Player;
									break;
                                case CellRepresentations.MegaPillCellRepresentation:
                                    currentEntity = new MegaPill(Field, x, y);
									
									break;
                                case CellRepresentations.GhostCellRepresentation:
							        var ghost = ghostFactory.GetNextGhost(Field, x, y);

                                    Ghosts.Add(ghost);

							        currentEntity = ghost;

                                    break;
                                case CellRepresentations.FruitCellRepresentation:
                                    var fruit = new Fruit(Field, x, y);

							        fruit.Eaten += (sender, args) =>
							        {
							            LevelPoints *= 2;
							            PillCount--;
							        };

							        PillCount++;

							        currentEntity = fruit;
                                    break;
								default:
									currentEntity = null;
									break;
							}

							Field[x, y].Owner = currentEntity;
						    
                            if (currentEntity != null)
						    {
						        Field[x, y].Movement += (sender, args) => currentEntity.NotifyMovement(args.Direction);
						    }
						}

						reader.Read();
						reader.Read();
					}
				}
			}
			catch (FileNotFoundException)
			{
				Console.Error.WriteLine(Resources.FileNotFoundErrorMessage);
			}
			catch (DirectoryNotFoundException)
			{
				Console.Error.WriteLine(Resources.FileNotFoundErrorMessage);
			}
		}

		public void MovePlayer(Direction direction)
		{
			Player.Move(direction);
		}

        private void Tick()
        {
            Timer.Enabled = false;

            if (GameFinished)
            {
                FinishGame();

                return;
            }

            if (LevelFinished)
            {
                LevelUp();

                return;
            }
            
            Player.Tick(PlayerDirection);

            foreach (var ghost in Ghosts)
            {
                ghost.Tick(IterationCount, Player);
            }

            IterationCount++;

            Timer.Enabled = true;
        }

        private void ResetEntities()
        {
            Player.Reset();

            foreach (var ghost in Ghosts)
            {
                ghost.Reset();
            }
        }

        void Start()
        {
            Started = true;
        }

        void Stop()
        {
            Started = false;
        }

        public void StartStop()
        {
            if (Started)
            {
                Stop();
            }
            else
            {
                Start();
            }
        }

        public void RestartCampaign()
        {
            ResetCampaign();
        }

        public void RestartLevel()
        {
            ResetLevel();
        }

        void LevelUp()
        {
            PreviousLevelPoints += LevelPoints;
            LevelNumber++;

            if (LevelNumber <= Levels.Instance.AvailableLevels.Count())
            {
                ResetLevel();
            }
            else
            {
                FinishGame();
            }
        }

        void FinishGame()
        {
            PlayerDied.Raise(this, new SaveRecordEventArgs { Score = CampaignPoints });

            ResetCampaign();
        }

        public void Dispose()
        {
            Timer.Dispose();
        }
    }
}
