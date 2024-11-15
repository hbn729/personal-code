import java.io.*;

class Vehicle1 {
    double speed;
    int power;

    void speedUp(int s) {
        speed = s + speed;
    }

    void speedDown(int d) {
        speed = speed - d;
    }

    void setPower(int p) {
        power = p;
    }

    int getPower() {
        return power;
    }

    double getSpeed() {
        return speed;
    }
}

class Village {
    static int waterAmount; // 模拟水井的水量
    int peopleNumber; // 村庄的人数
    String name; // 村庄的名字

    Village(String s) {
        name = s;
    }

    static void setWaterAmount(int m) {
        if (m > 0)
            waterAmount = m;
    }

    void drinkWater(int n) {
        if (waterAmount - n >= 0) {
            waterAmount = waterAmount - n;
            System.out.println(name + "喝了" + n + "升水");
        } else
            waterAmount = 0;
    }

    static int lookWaterAmount() {
        return waterAmount;
    }

    void setPeopleNumber(int n) {
        peopleNumber = n;
    }

    int getPeopleNumber() {
        return peopleNumber;
    }
}

public class load {
    public static void main(String args[]) {
        Vehicle1 car1, car2;
        car1 = new Vehicle1();
        car2 = new Vehicle1();
        car1.setPower(128);
        car2.setPower(76);
        System.out.println("car1的功率是：" + car1.getPower());
        System.out.println("car2的功率是：" + car2.getPower());
        car1.speedUp(80);
        car2.speedUp(80);
        System.out.println("car1目前的速度：" + car1.getSpeed());
        System.out.println("car2目前的速度：" + car2.getSpeed());
        car1.speedDown(10);
        car2.speedDown(20);
        System.out.println("car1目前的速度：" + car1.getSpeed());
        System.out.println("car2目前的速度：" + car2.getSpeed());

        Village.setWaterAmount(200);
        int leftWater = Village.waterAmount;
        System.out.println("水井中有 " + leftWater + " 升水");
        Village zhaoZhuang, maJiaHeZhi;
        zhaoZhuang = new Village("赵庄");
        maJiaHeZhi = new Village("马家河子");
        zhaoZhuang.setPeopleNumber(80);
        maJiaHeZhi.setPeopleNumber(120);
        zhaoZhuang.drinkWater(50);
        leftWater = maJiaHeZhi.lookWaterAmount();
        String name = maJiaHeZhi.name;
        System.out.println(name + "发现水井中有 " + leftWater + " 升水");
        maJiaHeZhi.drinkWater(100);
        leftWater = zhaoZhuang.lookWaterAmount();
        name = zhaoZhuang.name;
        System.out.println(name + "发现水井中有 " + leftWater + " 升水");
        int peopleNumber = zhaoZhuang.getPeopleNumber();
        System.out.println("赵庄的人口:" + peopleNumber);
        peopleNumber = maJiaHeZhi.getPeopleNumber();
        System.out.println("马家河子的人口:" + peopleNumber);

        try {
            ByteArrayOutputStream outByte = new ByteArrayOutputStream();
            byte[] byteContent = "mid-autumn festival".getBytes();
            outByte.write(byteContent);
            ByteArrayInputStream inByte = new ByteArrayInputStream(outByte.toByteArray());
            byte backByte[] = new byte[outByte.toByteArray().length];
            inByte.read(backByte);
            System.out.println(new String(backByte));
            CharArrayWriter outChar = new CharArrayWriter();
            char[] charContent = "中秋快乐".toCharArray();
            outChar.write(charContent);
            CharArrayReader inChar = new CharArrayReader(outChar.toCharArray());
            char backChar[] = new char[outChar.toCharArray().length];
            inChar.read(backChar);
            System.out.println(new String(backChar));
        } catch (IOException exp) {
        }
    }
}
