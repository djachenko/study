package ru.nsu.fit.djachenko.javaperfomance.lab6;


import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Lab6 extends ClassLoader
{
    public Class<?> loadClass(byte[] bytes)
    {
        return defineClass(null, bytes, 0, bytes.length);
    }

    public static void main(String args[])
    {
        String classDirectory = "res/ru/nsu/fit/djachenko/javaperfomance/lab6/";

        File directory = new File(classDirectory);
        String[] classes = directory.list();

        System.out.println(directory.getAbsolutePath());

        Lab6 classLoader = new Lab6();

        for (String className: classes)
        {
            try
            {
                byte[] bytes = Files.readAllBytes(Paths.get(classDirectory + className));

                Class<?> loadedClass = classLoader.loadClass(bytes);

                try
                {
                    Method getSecurityMessageMethod = loadedClass.getMethod("getSecurityMessage", null);

                    Object object = loadedClass.newInstance();

                    Object invokeResult = getSecurityMessageMethod.invoke(object);

                    System.out.println(loadedClass.getName() + ", " + invokeResult);
                }
                catch (NoSuchMethodException e)
                {}
                catch (InstantiationException | IllegalAccessException | InvocationTargetException e)
                {
                    e.printStackTrace();
                }
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }
    }
}
