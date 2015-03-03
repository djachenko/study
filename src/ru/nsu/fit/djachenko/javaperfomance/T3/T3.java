package ru.nsu.fit.djachenko.javaperfomance.T3;

public class T3 implements Runnable {
	private T3 other;

	public void setOther(T3 other) {
		this.other = other;
	}

	@Override
	public void run() {
		try {
			synchronized (other)
			{
				System.out.println("prewait");
				other.wait();
				System.out.println("postwait");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		T3 a = new T3();
		T3 b = new T3();

		a.setOther(b);
		b.setOther(a);

		new Thread(a).start();
		b.run();
	}
}
