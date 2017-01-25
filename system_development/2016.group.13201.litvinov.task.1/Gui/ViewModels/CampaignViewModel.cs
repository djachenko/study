using System.ComponentModel;
using GameCore;
using Gui.Properties;
using System.IO;
using System;

namespace Gui.ViewModels {
    internal sealed class CampaignViewModel : INotifyPropertyChanged {
        private readonly Campaign _campaign;
        public int Score => _campaign.Score;
        public int PacmanLives => _campaign.Lives;

        private CampaignStatus _campaignStatus = CampaignStatus.Gaming;

        public CampaignStatus CampaignStatus {
            get { return _campaignStatus; }
            set {
                _campaignStatus = value;
                OnPropertyChanged(nameof(CampaignStatus));
            }
        }

        private GameViewModel _activeGame; 

        public GameViewModel ActiveGame {
            get { return _activeGame; }
            set {
                _activeGame = value;
                OnPropertyChanged(nameof(ActiveGame));
                OnPropertyChanged(nameof(Score));
                OnPropertyChanged(nameof(PacmanLives));
            }
        }

        public HiscoresTable HiscoresTable { private get; set; }

        private void FlushHiscore() {
            var path = FsHelper.GetPathInAppdata((string)Settings.Default["HiscoresFilename"]);
            if (path == null) {
                ShowErrorService?.ShowError("Невозможно получить путь до файла с результатами.");
                return;
            }
            try {
                using (Stream stream = File.OpenWrite(path)) {
                    HiscoresTableIo.WriteHiscores(HiscoresTable, stream);
                }
            } catch (SystemException se) {
                ShowErrorService?.ShowError("Невозможно сохранить файл с результатами. " + se.Message);
            }
        }

        private void TryAddHiscore() {
            if (HiscoresTable == null || !HiscoresTable.CanPush(Score)) {
                return;
            }            
            string name = AskNameService?.AskName();
            if (name != null && name.Trim().Length != 0) {
                HiscoresTable.Push(new ScoreRecord(name, Score));
                FlushHiscore();
            }
        }

        public CampaignViewModel(Campaign campaign) {
            if (campaign == null) {
                throw new ArgumentException("campaign can't be null");
            }
            _campaign = campaign;
            _campaign.ActiveGameChanged += (sender, args) => ActiveGame = new GameViewModel(_campaign.ActiveGame);
            _campaign.ScoreChanged += (sender, args) => OnPropertyChanged(nameof(Score));
            _campaign.LivesChanged += (sender, args) => OnPropertyChanged(nameof(PacmanLives));
            _campaign.OnGameover += (sender, args) => {
                CampaignStatus = CampaignStatus.Gameover;
                TryAddHiscore();
            }; 
            _campaign.OnWin += (sender, args) => {
                CampaignStatus = CampaignStatus.Win;
                TryAddHiscore();
            };
        }

        public IAskNameService AskNameService { private get; set; }
        public IShowErrorService ShowErrorService { private get; set; }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
