package second.task3;

public class task3 {

    private static int ticketCount = 20; // 共享的票数
    private static final Object lock = new Object();

    public static void main(String[] args) {
        Station window1 = new Station("窗口1");
        Station window2 = new Station("窗口2");
        Station window3 = new Station("窗口3");

        window1.start();
        window2.start();
        window3.start();

        try {
            window1.join();
            window2.join();
            window3.join();
            System.out.println("票卖完了!");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    static class Station extends Thread {
        private String name;

        public Station(String name) {
            this.name = name;
        }

        @Override
        public void run() {
            while (true) {
                synchronized (lock) {
                    if (ticketCount > 0) {
                        int ticketNumber = ticketCount--;
                        System.out.println(name + "卖出了第" + (21 - ticketNumber) + "张票");
                    } else {
                        break;
                    }
                }
            }
        }
    }
}
