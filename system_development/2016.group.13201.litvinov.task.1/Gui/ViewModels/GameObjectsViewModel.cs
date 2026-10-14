using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using GameCore;

namespace Gui.ViewModels {
    class GameObjectsViewModel {
        public ObservableCollection<GameObjectViewModel> GameObjectViewModels { get; }

        public int Width { get; }

        public int Height { get; }

        public GameObjectsViewModel(List<GameObject> gameObjects, int fieldW, int fieldH) {
            if (gameObjects == null) {
                throw new ArgumentException("gameObjects can't be null");
            }
            Width = fieldW;
            Height = fieldH;
            var gameObjectViewModels = new ObservableCollection<GameObjectViewModel>();
            gameObjectViewModels.Clear();
            foreach (var gameObject in gameObjects) {
                gameObjectViewModels.Add(new GameObjectViewModel(gameObject));
            }
            GameObjectViewModels = gameObjectViewModels;
        }
    }
}
