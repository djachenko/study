using System;
using GameCore;

namespace Gui.ViewModels {
    internal sealed class HiscoreViewModel {
        private readonly ScoreRecord _record;
        public string Username => _record.UserName;
        public int Score => _record.Score;
        public HiscoreViewModel(ScoreRecord record) {
            if (record == null) {
                throw new ArgumentException("record can't be null");
            }
            _record = record;
        }
    }
}