package ru.nsu.fit.djachenko.javaperfomance.task1.lab3;

public class Lab3 {

	int coins = 1;

	void muliplyCoins(int ratio) {
		int newcoins = coins * ratio;
		coins = newcoins;
	}
	public static void main(String[] args) {
		Lab3 l2 = new Lab3();
		l2.muliplyCoins(10);
		l2.muliplyCoins(20);
	}
}