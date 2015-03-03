package ru.nsu.fit.djachenko.javaperfomance.T2;

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
		T2 a = new T2(true);
		T2 b = new T2(false);

		a.setOther(b);
		b.setOther(a);

		new Thread(a).start();

		b.run();
	}
}
