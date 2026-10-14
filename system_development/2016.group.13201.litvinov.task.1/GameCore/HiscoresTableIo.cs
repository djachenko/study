using System;
using System.Collections.Generic;
using System.IO;

namespace GameCore {
    public static class HiscoresTableIo {
        public static void WriteHiscores(HiscoresTable table, Stream outputStream) {
            if (table == null) {
                throw new ArgumentException("table can't be null", nameof(table));
            }
            if (outputStream == null) {
                throw new ArgumentException("stream can't be null", nameof(outputStream));
            }
            StreamWriter streamWriter = new StreamWriter(outputStream); 
            streamWriter.Write(table.MaxSize + Environment.NewLine);
            foreach (var scoreRecord in table) {
                streamWriter.Write(scoreRecord.UserName.Trim() + " " + scoreRecord.Score + Environment.NewLine);
            }
            streamWriter.Flush();
        }

        public static HiscoresTable ReadHiscores(Stream inputStream) {
            if (inputStream == null) {
                throw new ArgumentException("stream can't be null", nameof(inputStream));
            }
            int size = 0;
            var records = new List<ScoreRecord>();
            StreamReader streamReader = new StreamReader(inputStream);
            var line = streamReader.ReadLine();

            if (line != null) {
                size = Convert.ToInt32(line.Trim());
            }

            int linesRead = 0;
            while (linesRead < size && (line = streamReader.ReadLine()) != null) {
                line = line.Trim();
                int sepIdx = line.LastIndexOf(' ');
                string username = line.Substring(0, sepIdx).Trim();
                int score = Convert.ToInt32(line.Substring(sepIdx + 1).Trim());
                records.Add(new ScoreRecord(username, score));
                ++linesRead;
            }   
            
            return new HiscoresTable(size, records);
        }
    }
}
