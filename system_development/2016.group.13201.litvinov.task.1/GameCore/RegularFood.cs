using System;

namespace GameCore {
    internal class RegularFood : GameObject {
        public int EatScore { get; private set; }
        public bool IsAnnihilated { get; private set; }
        public override PointDouble Position { get; }
        public event EventHandler OnAnnihilate;

        protected RegularFood(PointInt position, string name, int eatScore) {
            Name = name;
            EatScore = eatScore;
            Position = PointCasts.IntToDouble(position);
            Direction = new PointInt(0,0);
        }

        internal void Annihilate() {
            if (IsAnnihilated) {
                return;
            }
            Name = "none";
            IsAnnihilated = true;
            EatScore = 0;
            OnAnnihilate?.Invoke(this, EventArgs.Empty);
        }

        internal override bool IsPassable => true;
        

        internal override void InteractWith(GameObject cause) {
        }

        public override PointInt Direction { get; }
    }
}
