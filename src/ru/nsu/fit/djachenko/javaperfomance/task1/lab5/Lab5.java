package ru.nsu.fit.djachenko.javaperfomance.task1.lab5;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;

public class Lab5 {
	static <T> T setLogging(final T obj) {
		Class<?>[] interfaces = obj.getClass().getInterfaces();

		InvocationHandler handler = (o, method, args) -> {
			System.out.println("CALLING: " + method.getName());
			System.out.println("RETURN VAL: " + method.getReturnType());

			return method.invoke(obj, args);
		};

		Object o = Proxy.newProxyInstance(obj.getClass().getClassLoader(), interfaces, handler);

		return (T)o;
	}

	public static void main(String[] args) {
		Runnable a = () -> System.out.println("RUnnde");

		setLogging(a).run();
	}
}
