package ru.nsu.fit.djachenko.javaperfomance.lab6;


import java.io.File;

public class Lab6
{
    public static void main(String args[]) {
        String classDirectory = args[0];
        /**
         * Создаем загрузчик модулей.
         */
        //ModuleLoader loader = new ModuleLoader(classDirectory, ClassLoader.getSystemClassLoader());

        /**
         * Получаем список доступных модулей.
         */
        File directory = new File(classDirectory);
        String[] classes = directory.list();

        /**
         * Загружаем и исполняем каждый модуль.
         */

        ClassLoader classLoader = ClassLoader.getSystemClassLoader();

        for (String className: classes)
        {
            if (className.endsWith(".class"))
            {
              /*  try
                {
                    String moduleName = className.split(".class")[0];

                }
                catch (ClassNotFoundException | IllegalAccessException | InstantiationException e)
                {
                    e.printStackTrace();
                }*/
            }
        }
    }
}
