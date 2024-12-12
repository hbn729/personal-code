class TestSleep1 {
    public static void main(String[] args) {
        BuyTicket ticket1 = new BuyTicket();
        BuyTicket ticket2 = new BuyTicket();
        BuyTicket ticket3 = new BuyTicket();
        new Thread(ticket1, "张三").start();
        new Thread(ticket2, "李四").start();
        new Thread(ticket3, "王五").start();
    }
}

class BuyTicket extends Thread {
    private int ticketNums = 10;

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