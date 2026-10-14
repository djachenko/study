using System;
using System.Collections.Generic;

namespace GameCore {
    public abstract class Hero : GameObject {
        public event EventHandler IntegerPointReached;

        private PointDouble _position;
        private PointInt _lastDirection;
        private readonly object _lastDirectionLock = new object();

        private readonly double _speed;
        private readonly PointDouble _initialPosition;
        protected bool IsMoving { get; private set; }

        internal bool IsNear(Hero gameObject) {
            if (gameObject == null) {
                return false;
            }
            return (gameObject.Position - Position).L2Norm() < 1;
        }

        private Field<GameObject> _staticGameObjects;

        private Field<GameObject> StaticGameObjects {
            get { return _staticGameObjects; }
            set {
                if (value == null) {
                    throw new ArgumentException("StaticGameObjects can't be null!");
                }
                _staticGameObjects = value;
            }
        }

        public override PointDouble Position => _position;

        private void SetPosition(PointDouble newPosition) {
            _position = newPosition;
        }

        protected internal PointInt? IntPosition { get; private set; }

        private PointInt LastDirection {
            get { return _lastDirection; }

            set {
                _lastDirection = value;
                IsMoving = true;
            }
        }

        private GhostRelationshipsMode _ghostRelationshipsMode;
        protected internal GhostRelationshipsMode GhostRelationshipsMode {
            protected get { return _ghostRelationshipsMode; }
            set {
                if (value == _ghostRelationshipsMode) {
                    return;
                }
                _ghostRelationshipsMode = value;
                OnGhostRelationshipsModeChanged();
            }
        }

        protected virtual void OnGhostRelationshipsModeChanged() {
        }

        public enum DirectionType { Left, Right, Up, Down };
        private static readonly Dictionary<DirectionType, PointInt> DirtypeToVector = 
            new Dictionary<DirectionType, PointInt>();

        static Hero() {
            DirtypeToVector.Add(DirectionType.Left, new PointInt(-1, 0));
            DirtypeToVector.Add(DirectionType.Right, new PointInt(1, 0));
            DirtypeToVector.Add(DirectionType.Up, new PointInt(0, -1));
            DirtypeToVector.Add(DirectionType.Down, new PointInt(0, 1));
        }

        public void SetPendingDirection(DirectionType directionType) {
            if (!DirtypeToVector.ContainsKey(directionType)) {
                throw new NotImplementedException("this dirtype is not supported: " + directionType);
            }
            lock (_lastDirectionLock) {
                LastDirection = DirtypeToVector[directionType];
            }
        }

        protected void SetPendingDirection(PointInt dir) {
            lock (_lastDirectionLock) {
                LastDirection = dir;
            }
        }

        private static readonly PointInt InitialDirection = new PointInt(1, 0);
        private const double InitialSpeed = 0.006667;

        protected Hero(Field<GameObject> staticGameObjects, PointInt initialPosition) {
            if (staticGameObjects == null) { 
                throw new ArgumentException("staticGameObjects can't be null");
            }
            StaticGameObjects = staticGameObjects;
            _position = PointCasts.IntToDouble(initialPosition);
            IntPosition = initialPosition;
            _initialPosition = _position;
            _lastDirection = InitialDirection;
            _direction = InitialDirection;
            _speed = InitialSpeed;
            IsMoving = false;
            Name = "common_hero";
        }

        internal void Respawn() {
            IsMoving = false;
            SetPosition(_initialPosition);
            OnPositionChanged();
        }

        // this should be <0.5 for OK working of IsIntegerPoint method
        private const double PositionRoundThreshold = 0.05; 

        // more (or exact) two MinStepDist have to bound in PositionRoundThreshold
        // so OK values are PositionRoundThreshold * (0.00...1 to 0.9)
        private const double MinStepDist = PositionRoundThreshold * 0.9; 

        private bool IsOpen(PointInt direction, double singleStepTime, out PointDouble nextPos) {
            nextPos = new PointDouble(0,0);
            if  (singleStepTime < 0) {
                return false;
            }

            nextPos = _position + PointCasts.IntToDouble(direction) * (_speed * singleStepTime);
            PointInt testPos = new PointInt();
            bool noCollision = true;

            for (int i = 0; i < (1 << PointDouble.Dims); ++i) {
                for (int j = 0; j < PointDouble.Dims; ++j) {
                    testPos[j] = (int)((i & (1 << j)) != 0
                                    ? Math.Floor(nextPos[j])
                                    : Math.Ceiling(nextPos[j]));
                }
                noCollision &= StaticGameObjects[testPos].IsPassable;
            }
            if (noCollision) {
                return true;
            }

            return false;
        }

        private bool CanChangeDirection(PointInt testDir) {
            return testDir.IsNonOrthogonal(Direction) || IntPosition != null;
        }

        private PointInt _prevIntPos;

        private void AtomaryMove(double singleStepTime) {
            if (singleStepTime < 0) {
                return;
            }
            IntPosition = null;
            if (_position.IsIntegerPoint(PositionRoundThreshold)) {
                IntPosition = PointCasts.DoubleToInt(_position, coord => (int) Math.Round(coord));
                if (!IntPosition.Value.EqualTo(_prevIntPos)) {
                    _position = PointCasts.IntToDouble(IntPosition.Value);
                    IntegerPointReached?.Invoke(this, EventArgs.Empty);
                }
                _prevIntPos = IntPosition.Value;
            }
            
            PointDouble nextPos;
            lock (_lastDirectionLock) {
                if (LastDirection.X == 0 && LastDirection.Y == 0) {
                    IsMoving = false;
                }
                if (CanChangeDirection(LastDirection) && IsOpen(LastDirection, singleStepTime, out nextPos)) {
                    _direction = LastDirection;
                }
                else if (IsOpen(Direction, singleStepTime, out nextPos)) {}
                else {
                    IsMoving = false;
                }
            }

            if (IsMoving) {
                _position = nextPos;
            }
        }

        internal void Move(double milliseconds) {
            if (milliseconds < 0) {
                throw new ArgumentException("milliseconds can't be negative", nameof(milliseconds));
            }
            double singleStepTime = MinStepDist / _speed;
            var oldPos = _position;
            while (milliseconds > 0) {
                AtomaryMove(singleStepTime);
                if (!IsMoving) {
                    break;
                }
                milliseconds -= singleStepTime;
            }

            if (!oldPos.EqualTo(_position)) {
                OnPositionChanged();
            }
            OnHeroMoveStepHappened();
        }

        protected virtual void OnHeroMoveStepHappened() { }

        internal override bool IsPassable => true;
        private PointInt _direction;
        public override PointInt Direction => _direction;
    }
}
