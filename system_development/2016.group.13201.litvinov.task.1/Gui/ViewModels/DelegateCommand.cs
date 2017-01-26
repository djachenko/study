using System;
using System.Windows.Input;

namespace Gui.ViewModels {
    internal sealed class DelegateCommand : ICommand {
        private readonly Action _action;

        public DelegateCommand(Action action) {
            _action = action;
            CanExecuteChanged?.Invoke(this, EventArgs.Empty);
        }

        public void Execute(object parameter) {
            _action?.Invoke();
        }

        public bool CanExecute(object parameter) {
            return true;
        }

        public event EventHandler CanExecuteChanged;
    }
}
