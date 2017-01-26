using System;
using GameCore;
using JetBrains.Annotations;

namespace GhostC {
    [PublicAPI]
    public sealed class GhostC : Ghost {
        private readonly GhostBfsDecider _decider;
        private const int EvilIdeaMaxAge = 1;
        private const int RescueIdeaMaxAge = 1;

        // some heuristic magic. as its value bigger, as more stable each state of madness
        private const int MadnessTauCounter = 30; 
        private const string NormalName = "ghost_c";
        private const string PursuitName = "ghost_c_p";

        protected override void OnGhostRelationshipsModeChanged() {
            Name = GhostRelationshipsMode == GhostRelationshipsMode.GhostsAreEvil
                ? NormalName
                : PursuitName;
        }
        public GhostC(Field<GameObject> staticGameObjects, PointInt initialPosition)
            : base(staticGameObjects, initialPosition) 
        {
            _decider = new GhostBfsDecider(staticGameObjects, EvilIdeaMaxAge, RescueIdeaMaxAge);
            _madnessSwitcher = new MadnessSwitcher(MadnessTauCounter, MadnessSwitcher.MadnessMode.Mad);
            Name = NormalName;
        }

        private sealed class MadnessSwitcher {
            public enum MadnessMode {
                Healthy,
                Mad
            };
            private readonly int _madnessTauCounter;
            public MadnessMode Mode { get; private set; }

            private int _madnessCounter;
            private readonly Random _random = new Random();

            public MadnessSwitcher(int madnessSwitchTauCounter, MadnessMode initialMadness) {
                _madnessTauCounter = madnessSwitchTauCounter;
                if (_madnessTauCounter <= 0) {
                    _madnessTauCounter = 1;
                }
                Mode = initialMadness;
                _madnessCounter = 0;
            }

            public void OneEvilStep() {
                ++_madnessCounter;
                if (Math.Exp(-1.0 * _madnessCounter / _madnessTauCounter) < _random.NextDouble()) {
                    _madnessCounter = 0;
                    Mode = Mode == MadnessMode.Healthy
                        ? MadnessMode.Mad
                        : MadnessMode.Healthy;
                }
            }

            public void OneFoodStep() {
                Mode = MadnessMode.Healthy;
                _madnessCounter = 0;
            }
        }

        private readonly MadnessSwitcher _madnessSwitcher;
        
        protected override void DecideAsEvil() {
            if (IntPosition == null) { return; }
            _madnessSwitcher.OneEvilStep();
            SetPendingDirection(_madnessSwitcher.Mode == MadnessSwitcher.MadnessMode.Mad
                ? _decider.DecideAsEvil(IntPosition.Value, LastPacmanIntPosition)
                : _decider.DecideAsFood(IntPosition.Value, LastPacmanIntPosition));
        }

        protected override void DecideAsFood() {
            if (IntPosition == null) { return; }
            _madnessSwitcher.OneFoodStep();
            SetPendingDirection(_decider.DecideAsFood(IntPosition.Value, LastPacmanIntPosition));
        }
    }
}
