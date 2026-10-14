using System;
using System.Data;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using System.Xml.Linq;

namespace PacMan.Helpers
{
    static class Cryptor
    {
        public static void Encrypt(XDocument document, string fileName)
        {                    
            using (var aes = Aes.Create())
            {
                if (aes == null)
                {
                    throw new NoNullAllowedException("Aes wasn't initialized");
                }

                var key = aes.Key;
                var iv = aes.IV;
                    
                using (var encryptor = aes.CreateEncryptor())
                {
                    using (var cryptoStream = new CryptoStream(new FileStream(fileName, FileMode.OpenOrCreate, FileAccess.Write), 
                        encryptor, CryptoStreamMode.Write))
                    {
                        document.Save(cryptoStream);

                        var builder = new StringBuilder();

                        builder.AppendLine(Convert.ToBase64String(iv));
                        builder.AppendLine(Convert.ToBase64String(key));

                        var keyfile = Encoding.Default.GetBytes(builder.ToString());
                        var keyfilePath = fileName + ".key";

                        using (var streamKey = new FileStream(keyfilePath, FileMode.OpenOrCreate, FileAccess.Write))
                        {
                            streamKey.Write(keyfile, 0, keyfile.Length);
                            streamKey.Flush();
                        }
                    }
                }
            }   
        }

        public static XDocument Decrypt(string fileName)
        {
            var keyFileName = fileName + ".key";

            using (var keyReader = new StreamReader(new FileStream(keyFileName, FileMode.Open, FileAccess.Read)))
            {
                var ivString = keyReader.ReadLine();
                var keyString = keyReader.ReadLine();

                if (ivString == null || keyString == null)
                {
                    throw new NoNullAllowedException("Key file is not valid");
                }
                
                using (var aes = Aes.Create())
                {
                    if (aes == null)
                    {
                        throw new NoNullAllowedException("Aes wasn't initialized");
                    }

                    aes.IV = Convert.FromBase64String(ivString.TrimEnd(' '));
                    aes.Key = Convert.FromBase64String(keyString.TrimEnd(' '));

                    using (var decryptor = aes.CreateDecryptor(aes.Key, aes.IV))
                    {
                        using (var cryptoStream = new CryptoStream(new FileStream(fileName, FileMode.Open, FileAccess.Read), 
                            decryptor, CryptoStreamMode.Read))
                        {
                            return XDocument.Load(cryptoStream);
                        }
                    }
                }
            }
        }
    }
}
