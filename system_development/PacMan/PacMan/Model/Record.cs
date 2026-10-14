using System.Xml.Linq;
using PacMan.Annotations;

namespace PacMan.Model
{
    public sealed class Record
    {
        private const string RecordEntryName = "Record";
        private const string NameEntryName = "Name";
        private const string ScoreEntryName = "Score";

        [UsedImplicitly]
        public string Name { get; private set; }
        public long Score { get; private set; }

        public Record(string name, long score)
        {
            Name = name;
            Score = score;
        }

        internal static Record Parse(XElement element)
        {
            if (element.Name == RecordEntryName)
            {
                var nameElement = element.Element(NameEntryName);
                var scoreElement = element.Element(ScoreEntryName);

                if (nameElement != null && scoreElement != null)
                {
                    var name = nameElement.Value;
                    var score = long.Parse(scoreElement.Value);

                    return new Record(name, score);
                }
            }

            return null;
        }

        internal XElement ToXml()
        {
            var element = new XElement(RecordEntryName);

            var name = new XElement(NameEntryName) { Value = Name };
            var score = new XElement(ScoreEntryName) { Value = Score.ToString() };

            element.Add(name);
            element.Add(score);

            return element;
        }
    }
}
