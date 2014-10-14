package ru.nsu.fit.djachenko.javaperfomance.T1T2;

public class T implements Runnable {
	private T other;
	private final boolean state;

	public T(boolean state) {
		this.state = state;
	}

	void setOther(T other) {
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
