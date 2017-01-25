using JetBrains.Annotations;

namespace GameCore {
    [UsedImplicitly]
    internal sealed class EmptyGameObject : GameObject {
        internal override bool IsPassable => true;
        public override PointDouble Position { get; }

        private EmptyGameObject(PointInt position) {
            Position = PointCasts.IntToDouble(position);
            Direction = new PointInt(0,0);
        }

        private static readonly IGameObjectLoader Loader
            = new DefaultGameObjectLoader((position, otherObjects) => new EmptyGameObject(position), ' ');
        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        public override PointInt Direction { get; }
        internal override void InteractWith(GameObject cause) {
        }
    }
}
