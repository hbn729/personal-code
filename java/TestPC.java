public class TestPC {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Productor p1 = new Productor();
		Consumer c1 = new Consumer("张三");
		Consumer c2 = new Consumer("李四");
		Consumer c3 = new Consumer("王五");
		p1.start();

		c1.start();
		c2.start();
		c3.start();
	}

}

class KFC {
	public static int hamburger = 5;
	public static Object lock = new Object();
}

class Productor extends Thread {
	public void run() {
		while (true) {
			synchronized (KFC.lock) {
				if (KFC.hamburger >= 20) {
					try {
						KFC.lock.wait();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				} else {
					KFC.hamburger++;
					System.out.println("生产者生产了一个汉堡！现在有" + KFC.hamburger
							+ "个数");
					KFC.lock.notifyAll();
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
	}
}

class Consumer extends Thread {
	public Consumer(String name) {
		super(name);
	}

	public void run() {
		while (true) {
			synchronized (KFC.lock) {
				if (KFC.hamburger > 0) {
					KFC.hamburger--;
					System.out.println(Thread.currentThread().getName() + " 吃了一个汉堡！还剩下 " +
							KFC.hamburger + "个");
					KFC.lock.notifyAll();

					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}

				} else {
					try {
						KFC.lock.wait();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}

			}
		}
	}
}