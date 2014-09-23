package ru.nsu.fit.djachenko.javaperfomance.task1.lab4;

public class Lab4 {

	static class Calculator {
		public int sum(int x, int y) {
			return x + y;
		}
	}

	static Calculator createCalculator() throws Exception {
		//todo use JavaAssist to inherit Calculator class,
		//overload sum() method
		//and add 1 to original return value, so 2 + 2 will be 5
		return new Calculator();
	}

	public static void main(String[] args) throws Exception {
		Calculator cal = createCalculator();
		System.out.println("2 + 2 = " + cal.sum(2, 2));
	}
}