using JetBrains.Annotations;

namespace GameCore {
    [UsedImplicitly]
    internal sealed class DotGameObject : RegularFood {
        private const int EatScores = 10;

        private static readonly IGameObjectLoader Loader
            = new DefaultGameObjectLoader((position,otherObjects) => new DotGameObject(position), '.');
        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        private DotGameObject(PointInt position) 
            : base(position, "dot", EatScores)
        {
        }
    }
}
