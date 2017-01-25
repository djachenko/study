using JetBrains.Annotations;

namespace GameCore {
    [UsedImplicitly]
    internal sealed class EnergizerGameObject : RegularFood {
        private const int EatScores = 500;

        private static readonly IGameObjectLoader Loader
            = new DefaultGameObjectLoader((position, otherObjects) => new EnergizerGameObject(position), '*');
        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        private EnergizerGameObject(PointInt position) 
            : base(position, "energizer", EatScores)
        {
        }
    }
}

