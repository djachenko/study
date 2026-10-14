using System;
using GameCore;
using JetBrains.Annotations;

namespace GhostA {
    [PublicAPI] 
    public sealed class GhostA : Ghost {
        private readonly GhostBfsDecider _decider;
        private static readonly Random Rnd = new Random();

        private const string NormalName = "ghost_a";
        private const string PursuitName = "ghost_a_p";

        protected override void OnGhostRelationshipsModeChanged() {
            Name = GhostRelationshipsMode == GhostRelationshipsMode.GhostsAreEvil
                ? NormalName
                : PursuitName;
        }

        public GhostA(Field<GameObject> staticGameObjects, PointInt initialPosition)
            : base(staticGameObjects, initialPosition) 
        {
            const int maxIdeaAge = 20;
            const int minIdeaAge = 1;
            _decider = new GhostBfsDecider(staticGameObjects, Rnd.Next(minIdeaAge, maxIdeaAge), Rnd.Next(minIdeaAge, maxIdeaAge));
            Name = NormalName;
        }
        
        protected override void DecideAsEvil() {
            if (IntPosition == null) { return; }
            SetPendingDirection(_decider.DecideAsEvil(IntPosition.Value, LastPacmanIntPosition));
        }

        protected override void DecideAsFood() {
            if (IntPosition == null) { return; }
            SetPendingDirection(_decider.DecideAsFood(IntPosition.Value, LastPacmanIntPosition));
        }

    }
}
