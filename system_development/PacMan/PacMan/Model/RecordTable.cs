using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using PacMan.Helpers;
using PacMan.Model.Exceptions;
using PacMan.Properties;

namespace PacMan.Model
{
    public sealed class RecordTable
    {
        private const int TableSize = 10;

        private static readonly Lazy<RecordTable> Lazy = new Lazy<RecordTable>(() => new RecordTable());

        public static RecordTable Instance
        {
            get { return Lazy.Value; }
        }

        public IEnumerable<Record> Records { get; private set; }

        private static string FilePath
        {
            get { return Resources.ResourcePath + Resources.RecordTableFile; }
        }

        private RecordTable()
        {
            Read();
        }

        private void Read()
        {
            try
            {
                var xDocument = Cryptor.Decrypt(FilePath + ".bin");

                if (xDocument.Root == null)
                {
                    Records = new List<Record>();
                }
                else
                {
                    Records = xDocument.Root.Elements()
                        .Select(Record.Parse)
                        .OrderByDescending(record => record.Score);
                }

            }
            catch (FileNotFoundException)
            {
                var list = new List<Record> 
                { 
                    new Record("Chuck", 100500), 
                    new Record("Allen, B.", 100499) 
                };


                Records = list;

                Dump();
            }
            catch (Exception e)
            {
                throw new ResourceFileNotValidException("Couldn't read field", e);
            }
        }

        private void Dump()
        {
            var document = new XDocument();

            var table = new XElement("RecordTable");

            foreach (var record in Records.Select(record => record.ToXml()))
            {
                table.Add(record);
            }

            document.Add(table);
            
            Cryptor.Encrypt(document, FilePath + ".bin");
        }

        public void Add(Record record)
        {
            Records = Records.Concat(new[] { record })
                .OrderByDescending(r => r.Score)
                .Take(TableSize);

            Dump();
        }

        public static void LoadAndCheck()
        {
            var recordTable = Lazy.Value;

            recordTable.DoNothing();
        }

        private void DoNothing()
        { }
    }
}
