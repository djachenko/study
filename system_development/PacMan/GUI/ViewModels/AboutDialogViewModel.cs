namespace GUI.ViewModels
{
    public sealed class AboutDialogViewModel
    {
        public string AboutText { get; set; }

        internal AboutDialogViewModel()
        {
            AboutText =
                "Hello! My name is Harry, and this is something pretending to be a PacMan game. " +
                "I've done it as a practice task for NSU system programming course.\n\n" +
                "All rights reserved and so on.\nSincerely, I don't mind if you'll change something and make this program better\n" +
                "2014-2015 ©";
        }
    }
}
