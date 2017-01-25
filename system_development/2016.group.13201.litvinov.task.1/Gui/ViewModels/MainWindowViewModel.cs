using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Input;
using Gui.Models;
using Gui.Properties;
using GameCore;

namespace Gui.ViewModels {
    internal sealed class MainWindowViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;

        private CampaignViewModel _campaignViewModel;

        public CampaignViewModel CampaignViewModel {
            get { return _campaignViewModel; }
            set {
                _campaignViewModel = value;
                _campaignViewModel.HiscoresTable = HiscoresTable;
                OnPropertyChanged(nameof(CampaignViewModel));
            }
        }

        public PacmanControlKeys PacmanControlKeys { get; } = new PacmanControlKeys();

        private KeybindingsEditorWindowViewModel _keybindingsEditorWindowViewModel;

        private void SetupKeybindings() {
            IKeybindingsSource[] kbSources = { PacmanControlKeys };

            KeybindingsGroup appKeybindingsGroup = new KeybindingsGroup();
            foreach (var src in kbSources) {
                appKeybindingsGroup.All.AddRange(src.GetKeybindings());
            }
            _keybindingsEditorWindowViewModel = new KeybindingsEditorWindowViewModel(appKeybindingsGroup);
        }

        private void SetupHiscoresTable() {
            var path = FsHelper.GetPathInAppdata((string)Settings.Default["HiscoresFilename"]);
            if (!File.Exists(path)) {
                CreateEmptyHiscores(path);
            }
            LoadHiscores();
        }

        public MainWindowViewModel() {
            SetupKeybindings();
            SetupHiscoresTable();
        }

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private static Game LoadGameFromStream(Stream stream) {
            Game game = new Game();
            game.SetupGame(FieldIo.ReadField(stream));
            return game;
        }

        private void StartCampaignFromList(List<Game> campaignGames) {
            var campaign = new Campaign(campaignGames);
            CampaignViewModel = new CampaignViewModel(campaign);
            campaign.Start();
        }

        private void CatchHandleErrors(Action a) {
            try {
                a();
            }
            catch (FieldIoError e) {
                ShowErrorService?.ShowError("Ошибка формата файла с полем. " + e.Message);
            } catch (GhostsLoadException e) {
                ShowErrorService?.ShowError("Ошибка загрузки приведений. " + e.Message);
            } catch (GhostCreateException e) {
                ShowErrorService?.ShowError("Ошибка создания приведений. " + e.Message);
            } catch (Exception e) {
                ShowErrorService?.ShowError("Ошибка инициализации кампании. " + e.Message);
            }
        }

        private static Game LoadGameFromResource(string resourceName) {
            var resourceStream = Application.GetResourceStream(new Uri(resourceName, UriKind.Relative));
            if (resourceStream != null) {
                return LoadGameFromStream(resourceStream.Stream);
            }
            throw new SystemException("Невозможно загрузить игру из файла-ресурса.");
        }
        
        public ICommand StartEmbeddedCampaign => new DelegateCommand(() => {
            CatchHandleErrors(() => {
                var campaignGames = new List<Game> {
                    LoadGameFromResource("Resources/level_1.txt"),
                    LoadGameFromResource("Resources/level_2.txt"),
                    LoadGameFromResource("Resources/level_3.txt")
                };
                StartCampaignFromList(campaignGames);
            });
        });

        public IOpenFileService OpenFileService { private get; set; }

        public ICommand StartGameFromFile => new DelegateCommand(() => {
            string fileName;
            if (OpenFileService == null || (fileName = OpenFileService.GetFileName()) == null) { 
                return;
            }
            CatchHandleErrors(() => {
                Game game;
                using (Stream stream = File.OpenRead(fileName)) {
                    game = LoadGameFromStream(stream);
                }
                StartCampaignFromList(new List<Game> { game });
            });
        });

        public ICommand EditKeybindings => new DelegateCommand(() => {
            ShowKeybindingsEditorService?.ShowKeybindingsEditor(_keybindingsEditorWindowViewModel);
        });

        private void CreateEmptyHiscores(string path) {
            HiscoresTable tbl = new HiscoresTable((int)Settings.Default["HiscoresSize"]);
            try {
                using (Stream stream = File.OpenWrite(path)) {
                    HiscoresTableIo.WriteHiscores(tbl, stream);
                }
            }
            catch (SystemException se) {
                ShowErrorService?.ShowError("Невозможно создать файл с результатами. " + se.Message);
            }
        }

        private HiscoresTable _hiscoresTable;

        private HiscoresTable HiscoresTable {
            get { return _hiscoresTable; }
            set {
                _hiscoresTable = value;
                if (CampaignViewModel != null) {
                    CampaignViewModel.HiscoresTable = value;
                }
            }
        }

        private bool LoadHiscores() {
            var path = FsHelper.GetPathInAppdata((string)Settings.Default["HiscoresFilename"]);
            try {
                using (Stream stream = File.OpenRead(path)) {
                    HiscoresTable = HiscoresTableIo.ReadHiscores(stream);
                }
                return true;
            } catch (SystemException se) {
                ShowErrorService?.ShowError("Невозможно загрузить файл с результатами. " + se.Message);
                return false;
            }
        }

        public ICommand ShowHiscores => new DelegateCommand(() => {
            if (LoadHiscores()) {
                ShowHiscoresService?.ShowHiscores(HiscoresTable);
            }
        });

        public IShowErrorService ShowErrorService { private get; set; }
        public IShowKeybindingsEditorService ShowKeybindingsEditorService { private get; set; }
        public IShowHiscoresService ShowHiscoresService { private get; set; }
    }
}
