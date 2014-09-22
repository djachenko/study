package ru.nsu.fit.djachenko.javaperfomance.task1.lab2;

public class P2 {
	public static void main(String[] args) {
		StringBuilder s = new StringBuilder();
		for (int i = 0; i < 10000; ++i) {
			s.append(" ").append(String.valueOf(i));
		}
		System.out.println(s.length());
	}
}
