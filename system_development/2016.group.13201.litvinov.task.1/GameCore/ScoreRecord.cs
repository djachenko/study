using System;

namespace GameCore {
    public sealed class ScoreRecord {
        public string UserName { get; }
        public int Score { get; }

        public ScoreRecord(string userName, int score) {
            if (userName == null || userName.Trim().Length == 0) {
                throw new ArgumentException("userName can't be null or empty");
            }
            if (score < 0) {
                throw new ArgumentException("score can't be negative");
            }
            
            UserName = userName;
            Score = score;
        }
    }
}
