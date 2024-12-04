package secondClassWork;

class SpeakCar implements Runnable {
    public void run() {
        for (int i = 1; i <= 20; i++) {
            System.out.print("线程2第" + i + "次 ");
        }
    }
}

class SpeakElephant implements Runnable {
    public void run() {
        for (int i = 1; i <= 20; i++) {
            System.out.print("线程1第" + i + "次 ");
        }
    }
}

class ThreadA extends Thread {
    public void run() {
        for (int i = 1; i <= 100; i++) {
            System.out.println("ThreadA" + i);
        }
    }
}

class ThreadB implements Runnable {
    public void run() {
        for (int i = 1; i <= 100; i++) {
            System.out.println("ThreadB" + i);
        }
    }
}

public class Example12_1 {
    public static void main(String args[]) { // 主线程
        // second
        SpeakElephant speakElephant;
        SpeakCar speakCar;
        speakElephant = new SpeakElephant(); // 创建线程
        speakCar = new SpeakCar(); // 创建线程
        Thread t1 = new Thread(speakElephant);
        Thread t2 = new Thread(speakCar);
        t1.start();
        t2.start(); 
        for (int i = 1; i <= 15; i++) {
            System.out.print("主线程第" + i + "次 ");
        }
        // third
        ThreadA a = new ThreadA();
        ThreadB b = new ThreadB();
        Thread b1 = new Thread(b);
        a.start();
        b1.start();
        for (int i = 1; i <= 100; i++) {
            System.out.println("mainThread" + i);
        }
    }
}
