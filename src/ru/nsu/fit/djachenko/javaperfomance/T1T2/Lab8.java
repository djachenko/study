package ru.nsu.fit.djachenko.javaperfomance.T1T2;

public class Lab8 {
	static void work() {
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		T a = new T(true);
		T b = new T(false);

		a.setOther(b);
		b.setOther(a);

		new Thread(a).start();

		b.run();
	}
}
