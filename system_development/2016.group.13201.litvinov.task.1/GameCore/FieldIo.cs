using System.Collections.Generic;
using System.IO;

namespace GameCore {
    public static class FieldIo {

        private static void ParseFieldLine(int lineY, string parsedLine, Field<char> field) {
            if (field == null) {
                return;
            }
            for (int x = 0; x < parsedLine.Length; ++x) {
                field[x, lineY] = parsedLine[x];
            }
        }

        private static bool ValidateDims(Field<char> field) {
            if (field == null) {
                return false;
            }
            const int minFieldWidth = 2;
            const int minFieldHeight = 2;
            return field.Width > minFieldWidth && field.Height > minFieldHeight;
        }

        private static bool ValidatePerimeter(Field<char> field) {
            if (field == null) {
                return false;
            }
            for (int i = 0; i <= 1; ++i) {
                for (int j = 0; j < field.Height; ++j) {
                    if (field[i * (field.Width-1), j] != '#')
                        return false;
                }
            }

            for (int i = 0; i <= 1; ++i) {
                for (int j = 0; j < field.Width; ++j) {
                    if (field[j, i * (field.Height-1)] != '#')
                        return false;
                }
            }

            return true;
        }

        private static void ValidateField(Field<char> field) {
            if (!ValidateDims(field)) { 
                throw new FieldIoError("Field dimensions must be bigger than 2x2");
            }

            if (!ValidatePerimeter(field)) {
                throw new FieldIoError("Field must be rounded with wall");
            }

            if (!ValidatePacman(field)) {
                throw new FieldIoError("Field must has 1 pacman");
            }
        }

        private static bool ValidatePacman(Field<char> field) {
            if (field == null) {
                return false;
            }
            int pacmanCount = 0;
            for (int i = 0; i < field.Width; ++i) {
                for (int j = 0; j < field.Height; ++j) {
                    if (field[i, j] == '\\') {
                        pacmanCount++;
                    }
                }
            }
            return pacmanCount == 1;
        }

        public static Field<char> ReadField(Stream inputStream) {
            if (inputStream == null) {
                return null;
            }
            List<string> lines = new List<string>();
            const int unknownLen = -1;
            int len = unknownLen;
            using (StreamReader sr = new StreamReader(inputStream)) {
                string line;
                while ((line = sr.ReadLine()) != null) {
                    if (len != unknownLen && line.Length != len) {
                        throw new FieldIoError("All strings in field file must have same length");
                    }
                    len = line.Length;
                    lines.Add(line);
                }
            }

            Field<char> field = new Field<char>(len, lines.Count);
            int lineY = 0;
            foreach (var l in lines) {
                ParseFieldLine(lineY++, l, field);
            }

            ValidateField(field);

            return field;
        }
    }
}
