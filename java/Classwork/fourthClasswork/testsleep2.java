public class testsleep2 {
    public static void main(String[] args) {
        BuyTicket ticket = new BuyTicket();
        new Thread(ticket, "张三").start();
        new Thread(ticket, "李四").start();
        new Thread(ticket, "王五").start();
    }
}

class BuyTicket implements Runnable {
    private int ticketNums = 10;

    @Override
    public void run() {
        while (true) {
            buyticket();
             if (ticketNums<=0) {
                break;
            }

        }
    }

    public synchronized void buyticket() {
        if (ticketNums > 0) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            System.out.println(Thread.currentThread().getName()
                    + "买了第" + ticketNums-- + "票");

        }
    }
}