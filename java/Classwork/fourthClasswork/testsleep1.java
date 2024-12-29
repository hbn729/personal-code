class TestSleep1 {
    public static void main(String[] args) {
        new BuyTicket("张三").start();
        new BuyTicket("李四").start();
        new BuyTicket("王五").start();
    }
}

class BuyTicket extends Thread {
    public BuyTicket(String name) {
        super(name);
    }

    private static int ticketNums = 10;

    @Override
    public void run() {
        while (true) {
            synchronized (BuyTicket.class) {
                if (ticketNums > 0) {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }

                    System.out.println(Thread.currentThread().getName()
                            + "买了第" + ticketNums-- + "票");
                } else {
                    break;
                }
            }

        }
    }
}