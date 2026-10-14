using System;
using System.ComponentModel;

namespace PacMan.Helpers
{
    public static class EventHelper
    {
        public static void Raise(this EventHandler source, object sender)
        {
            if (source != null)
            {
                source(sender, EventArgs.Empty);
            }
        }

        public static void Raise(this PropertyChangedEventHandler source, object sender, PropertyChangedEventArgs args)
        {
            if (source != null)
            {
                source(sender, args);
            }
        }

        public static void Raise<T>(this EventHandler<T> source, object sender, T args) where T : EventArgs
        {
            if (source != null)
            {
                source(sender, args);
            }
        }
    }
}
