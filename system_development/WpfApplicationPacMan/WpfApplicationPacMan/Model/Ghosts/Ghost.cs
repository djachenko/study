namespace WpfApplicationPacMan.Model.Ghosts
{
    sealed class Ghost
    {
        private readonly GhostAI _ghostAI;

        #region properties
        public Position Position
        {
            get;
            set;
        }
        public bool IsAttackModeOn
        {
            get
            {
                return _ghostAI.IsAttackModeOn; 
            }
            set
            {
                _ghostAI.IsAttackModeOn = value;
            }
        }
        #endregion properties


        public Ghost(GhostAI ghostAI, Position position, int[,] matrix)
        {
            _ghostAI = ghostAI;
            _ghostAI.SetMatrix(matrix);
            IsAttackModeOn = ghostAI.IsAttackModeOn;
            Position = position;
        }

        public void Move(Position playerPosition)
        {
            Position = _ghostAI.GetNextPosition(Position, playerPosition);
        }
    }
}
