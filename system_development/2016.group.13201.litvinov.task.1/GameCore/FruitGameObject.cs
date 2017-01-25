using JetBrains.Annotations;

namespace GameCore {
    [UsedImplicitly]
    internal sealed class FruitGameObject : RegularFood {
        private const int EatScores = 2000;

        private static readonly IGameObjectLoader Loader 
            = new DefaultGameObjectLoader((position, otherObjects) => new FruitGameObject(position), '%');
        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        private FruitGameObject(PointInt position) 
            : base(position, "fruit", EatScores)
        {
        }
    }
}
