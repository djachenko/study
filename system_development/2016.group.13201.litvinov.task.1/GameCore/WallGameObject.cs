using JetBrains.Annotations;

namespace GameCore {
    [UsedImplicitly]
    internal sealed class WallGameObject : GameObject {
        internal override bool IsPassable => false;
        public override PointDouble Position { get; }

        private WallGameObject(PointInt position) {
            Name = "wall";
            Position = PointCasts.IntToDouble(position);
            Direction = new PointInt(0,0);
        }

        private static readonly IGameObjectLoader Loader
            = new DefaultGameObjectLoader((position, otherObjects) => new WallGameObject(position), '#');
        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        public override PointInt Direction { get; }
        internal override void InteractWith(GameObject cause) {
        }
    }
}
