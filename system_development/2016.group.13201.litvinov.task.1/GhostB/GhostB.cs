using GameCore;
using JetBrains.Annotations;

namespace GhostB {
    [PublicAPI] 
    public sealed class GhostB : Ghost {
        private const string NormalName = "ghost_b";
        private const string PursuitName = "ghost_b_p";

        protected override void OnGhostRelationshipsModeChanged() {
            Name = GhostRelationshipsMode == GhostRelationshipsMode.GhostsAreEvil
                ? NormalName
                : PursuitName;
        }

        public GhostB(Field<GameObject> staticGameObjects, PointInt initialPosition)
            : base(staticGameObjects, initialPosition) 
        {
            GhostRandomDecider = new GhostRandomDecider(staticGameObjects);
            Name = NormalName;
        }

        private GhostRandomDecider GhostRandomDecider { get; }

        protected override void DecideAsEvil() {
            if (IntPosition == null) { return; }
            SetPendingDirection(GhostRandomDecider.DecideRandom(IntPosition.Value));
        }

        protected override void DecideAsFood() {
            if (IntPosition == null) { return; }
            SetPendingDirection(GhostRandomDecider.DecideRandom(IntPosition.Value));
        }
    }
}
