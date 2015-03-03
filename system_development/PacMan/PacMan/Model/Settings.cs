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
    public sealed class Settings
    {
        private const string RootEntryName = "Settings";
        private const string SettingEntryName = "Setting";
        private const string DirectionEntryName = "Direction";
        private const string KeyEntryName = "Key";

        private static string FilePath
        {
            get { return Resources.ResourcePath + Resources.SettingsFile; }
        }

        private static readonly Lazy<Settings> Lazy = new Lazy<Settings>(() => new Settings());

        public static Settings Instance
        {
            get { return Lazy.Value; }
        }

        public Dictionary<Direction, string> Keys { get; private set; }

        public event EventHandler SettingsChanged;

        private Settings()
        {
            Keys = new Dictionary<Direction, string>();

            foreach (var direction in Direction.Values)
            {
                Keys[direction] = string.Empty;
            }

            Keys.Remove(Direction.Place);

            Read();
        }

        private void Read()
        {
            try
            {
                var xDocument = XDocument.Load(FilePath);

                if (xDocument.Root != null)
                {
                    foreach (var settingEntry in xDocument.Root.Elements())
                    {
                        var directionEntry = settingEntry.Element(DirectionEntryName);
                        var keyEntry = settingEntry.Element(KeyEntryName);

                        if (directionEntry != null && keyEntry != null)
                        {
                            var direction = Direction.Parse(directionEntry.Value);

                            if (direction != null)
                            {
                                Keys[direction] = keyEntry.Value;
                            }
                        }
                    }
                }
            }
            catch (FileNotFoundException)
            {
                PrepareDefaults();

                Dump();
            }
            catch (Exception e)
            {
                PrepareDefaults();
                Dump();

                throw new SettingsNotValidException("Error while loading settings", e);
            }
        }

        private void PrepareDefaults()
        {
            Keys[Direction.Left] = "Left";
            Keys[Direction.Up] = "Up";
            Keys[Direction.Right] = "Right";
            Keys[Direction.Down] = "Down";
        }

        public void ResetDefaults()
        {
            PrepareDefaults();
            
            Dump();

            SettingsChanged.Raise(this);
        }

        private void Dump()
        {
            var document = new XDocument();

            var allSettingsEntry = new XElement(RootEntryName);

            foreach (var key in Keys)
            {
                var directionEntry = new XElement(DirectionEntryName) { Value = key.Key.Name };
                var keyEntry = new XElement(KeyEntryName) { Value = key.Value };

                var settingEntry = new XElement(SettingEntryName);

                settingEntry.Add(directionEntry);
                settingEntry.Add(keyEntry);

                allSettingsEntry.Add(settingEntry);
            }

            document.Add(allSettingsEntry);

            document.Save(FilePath);
        }

        public void Change(Direction direction, string newSetting)
        {
            if (Keys.Any(keyPair => keyPair.Value == newSetting && keyPair.Key != direction))
            {
                throw new KeyBindedException("Key " + newSetting + " is already binded to " + direction.Name + " direction.");
            }

            Keys[direction] = newSetting;

            Dump();

            SettingsChanged.Raise(this);
        }

        public void Remove(Direction direction)
        {
            Change(direction, string.Empty);
        }
    }
}
