package ru.nsu.fit.djachenko.javaperfomance.lab7;

import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.lang.instrument.Instrumentation;
import java.security.ProtectionDomain;

public class Lab7Agent
{
	public static void premain(String args, Instrumentation instrumentation)
	{
		instrumentation.addTransformer(new ClassFileTransformer()
		{
			private int count = 0;

			@Override
			public byte[] transform(ClassLoader loader, String className,
			                        Class<?> classBeingRedefined,
			                        ProtectionDomain protectionDomain,
			                        byte[] classFileBuffer) throws IllegalClassFormatException
			{
				count++;

				System.out.println("loaded class #" + count +": " + className.replaceAll("/", ".") +
				                   "has length of " + classFileBuffer.length + " bytes");

				return null;
			}
		});
	}
}