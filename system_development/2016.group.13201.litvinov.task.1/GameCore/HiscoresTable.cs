using System;
using System.Collections;
using System.Collections.Generic;

namespace GameCore {
    public sealed class HiscoresTable : IEnumerable<ScoreRecord> {
        private readonly List<ScoreRecord> _table = new List<ScoreRecord>();

        internal int MaxSize { get; }

        private readonly ScoreRecordComparer _comparer = new ScoreRecordComparer();

        public HiscoresTable(int maxSize, IEnumerable<ScoreRecord> records = null) {
            if (maxSize < 0) {
                throw new ArgumentException("maxSize can't be negative", nameof(maxSize));
            }

            MaxSize = maxSize;
            if (records != null) {
                _table = new List<ScoreRecord>(records);
                _table.Sort(_comparer);
                PopOut();
            }
        }

        public bool CanPush(int score) {
            if (MaxSize == 0) {
                return false;
            }
            if (_table.Count == 0) {
                return true;
            }
            return score >= _table[0].Score || _table.Count < MaxSize;
        }

        public void Push(ScoreRecord scoreRecord) {
            if (scoreRecord == null) {
                throw new ArgumentException("scoreRecord can't be null");
            }

            int searchRes = _table.BinarySearch(scoreRecord, _comparer);
            if (searchRes < 0) { 
                _table.Insert(~searchRes, scoreRecord);
            } else {
                while (searchRes < _table.Count && _comparer.Compare(_table[searchRes], scoreRecord) <= 0) {
                    ++searchRes;
                }
                _table.Insert(searchRes, scoreRecord);
            }

            if (_table.Count > MaxSize) {
                PopOut();
            }
        }

        private void PopOut() {
            _table.RemoveRange(0, Math.Max(0, _table.Count - MaxSize));
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }

        public IEnumerator<ScoreRecord> GetEnumerator() {
            return _table.GetEnumerator();
        }

        private sealed class ScoreRecordComparer : IComparer<ScoreRecord> {
            public int Compare(ScoreRecord x, ScoreRecord y) {
                return x.Score.CompareTo(y.Score);
            }
        }
    }
}
