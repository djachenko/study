using GameCore;
using System.Collections.Generic;
using System.Windows.Input;

namespace Gui.ViewModels {
    internal sealed class HeroesViewModel : GameObjectsViewModel {
        
        private readonly Hero _pacmanGameObject;

        public ICommand PacmanGoLeftCommand 
            => new DelegateCommand(() => _pacmanGameObject?.SetPendingDirection(Hero.DirectionType.Left));
        public ICommand PacmanGoRightCommand
            => new DelegateCommand(() => _pacmanGameObject?.SetPendingDirection(Hero.DirectionType.Right));
        public ICommand PacmanGoUpCommand 
            => new DelegateCommand(() => _pacmanGameObject?.SetPendingDirection(Hero.DirectionType.Up));
        public ICommand PacmanGoDownCommand 
            => new DelegateCommand(() => _pacmanGameObject?.SetPendingDirection(Hero.DirectionType.Down));

        public HeroesViewModel(List<GameObject> gameObjects, int fieldW, int fieldH) 
            : base(gameObjects, fieldW, fieldH)
        {
            foreach (var gameObject in gameObjects) {
                var pacman = gameObject as Pacman;
                if (pacman != null) {
                    _pacmanGameObject = pacman;
                }
            }
        }
    }
}
