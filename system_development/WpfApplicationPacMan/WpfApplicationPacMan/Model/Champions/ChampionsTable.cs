using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using WpfApplicationPacMan.Properties;

namespace WpfApplicationPacMan.Model.Champions
{
    class ChampionsTable
    {
        private const int Capacity = 10;
        private static readonly string RootDir = Directory.GetCurrentDirectory();
        private static readonly string PathToChampions = RootDir + @"\Resources\Champions\";
        private static readonly string ChampionsFileName = PathToChampions + "Champions.txt";

        public SortedList<int, string> Dictionary
        {
            get;
            private set;
        }

        public ChampionsTable()
        {
            Dictionary = new SortedList<int, string>(new DuplicateKeyComparer<int>()) { Capacity = Capacity };
            try
            {
                using (var sr = new StreamReader(ChampionsFileName))
                {
                    String s;
                    while ((s = sr.ReadLine()) != null && Dictionary.Count <= Capacity)
                    {
                        var str = s.Split(' ');
                        if (str[0] == null || str[1] == null)
                        {
                            continue;
                        }
                        var score = int.Parse(str[0]);
                        var name = str[1];

                        Dictionary.Add(score, name);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(Resources.Field_Field_The_file_could_not_be_read_);
                Console.WriteLine(e.Message);
            }
        }

        private class DuplicateKeyComparer<TKey> : IComparer<TKey> where TKey : IComparable
        {
            #region IComparer<TKey> Members
            public int Compare(TKey x, TKey y)
            {
                if (x == null)
                {
                    throw new ArgumentNullException("x");
                }
                if (y == null)
                {
                    throw new ArgumentNullException("y");
                }

                var result = y.CompareTo(x);
                return result == 0 ? 1 : result;
            }

            #endregion
        }

        ~ChampionsTable()
        {
            try
            {
                using (var file = new StreamWriter(ChampionsFileName))
                {
                    foreach (var variable in Dictionary)
                    {
                        file.WriteLine(variable.Key + " " + variable.Value);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(Resources.Field_Field_The_file_could_not_be_read_);
                Console.WriteLine(e.Message);
            }
        }

        public void Add(String name, int score)
        {
            if (Dictionary.Count >= Capacity)
            {
                Dictionary.RemoveAt(Capacity - 1);
                Dictionary.Add(score, name);
            }
            else
            {
                Dictionary.Add(score, name);
            }
        }

        public bool IsNewRecordsman(int score)
        {
            return Dictionary.Count != Capacity || Dictionary.Any(variable => variable.Key < score);
        }
    }

}
