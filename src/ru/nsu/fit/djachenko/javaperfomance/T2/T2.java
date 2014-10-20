package ru.nsu.fit.djachenko.javaperfomance.T2;

public class T2 implements Runnable {
	private T2 other;
	private final boolean state;

	public T2(boolean state) {
		this.state = state;
	}

	void setOther(T2 other) {
		this.other = other;
	}

	@Override
	public void run() {
		if (state) {
			synchronized (other) {
				try {
					System.out.println("wait");
					other.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		while (true) {
			System.out.println("work " + this);
			Lab8.work();

			synchronized (this) {
				notify();
			}

			synchronized (other) {
				try {
					System.out.println("wait");
					other.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
