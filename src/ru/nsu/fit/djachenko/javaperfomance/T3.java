package ru.nsu.fit.djachenko.javaperfomance;

public class T3 implements Runnable {
	private T3 other;

	public void setOther(T3 other) {
		this.other = other;
	}

	@Override
	public void run() {
		try {
			other.wait();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {

	}
}
