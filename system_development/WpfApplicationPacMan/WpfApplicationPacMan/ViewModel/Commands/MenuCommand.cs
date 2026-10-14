using System;
using System.Windows.Input;

namespace WpfApplicationPacMan.ViewModel.Commands
{
    public class MenuCommand : ICommand
    {
        readonly Action<object> _execute;
        readonly Predicate<object> _canExecute;

        #region constructors

        public MenuCommand(Action<object> execute)
        {
            _execute = execute;
        }

        public MenuCommand(Action<object> execute, Predicate<object> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            _execute = execute;
            _canExecute = canExecute;
        }
        #endregion

        #region ICommand members

        //Событие CanExecuteChanged, часть реализации интерфейса ICommand, 
        //имеет ряд интересных функций. Оно передает подписку на событие 
        //событию CommandManager.RequerySuggested. Это гарантирует, что 
        //командная инфраструктура WPF опрашивает все объекты RelayCommand, 
        //могут ли они совершать выполнение при любом обращении к встроенным командам. 

        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return _canExecute == null || _canExecute(parameter);
        }

        public void Execute(object parameter)
        {
            _execute(parameter);
        }
        #endregion

    }
}
