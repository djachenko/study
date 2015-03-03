package ru.nsu.fit.djachenko.javaperfomance.lab4;

import javassist.util.proxy.MethodHandler;
import javassist.util.proxy.Proxy;
import javassist.util.proxy.ProxyFactory;

public class Lab4 {
	static class Calculator {
		public int sum(int x, int y) {
			return x + y;
		}
	}

	private static Calculator createCalculator() throws Exception {
        ProxyFactory proxyFactory = new ProxyFactory();

        proxyFactory.setSuperclass(Calculator.class);
        proxyFactory.setFilter(m -> "sum".equals(m.getName()));

        Class calculatorProxyClass = proxyFactory.createClass();

        Calculator calculatorProxy = (Calculator)calculatorProxyClass.newInstance();

        if (calculatorProxy != null) {
            MethodHandler methodHandler = (self, m, proceed, args) -> (Integer)proceed.invoke(self, args) + 1;

            ((Proxy)calculatorProxy).setHandler(methodHandler);
        }

        return calculatorProxy;
	}

	public static void main(String[] args) throws Exception {
		Calculator cal = createCalculator();

		System.out.println("2 + 2 = " + cal.sum(2, 2));
	}
}