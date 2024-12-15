
import java.util.Random;
import java.util.Scanner;

public class GuessingGame {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();
        boolean playAgain = true;// 是否继续游戏

        while (playAgain) {
            int Answer = random.nextInt(100) + 1; // 生成1到100之间的随机数
            int tryAnt = 0;
            int userAnswer = 0;

            System.out.println("猜一个1到100之间的整数：");

            while (userAnswer != Answer) {
                userAnswer = scanner.nextInt(); // 用户输入猜测
                tryAnt++; // 增加猜测次数

                if (userAnswer < Answer) {
                    System.out.println("猜小了，请再试一次：");
                } else if (userAnswer > Answer) {
                    System.out.println("猜大了，请再试一次：");
                } else {
                    System.out.println("猜对了！你总共猜了 " + tryAnt + " 次。");
                }
            }

            // 提供重新开始或退出的选项
            System.out.println("重新开始？ (y/n)");
            char choice = scanner.next().charAt(0);
            playAgain = (choice == 'y' || choice == 'Y');
        }

        System.out.println("游戏结束");
        scanner.close();
    }
}