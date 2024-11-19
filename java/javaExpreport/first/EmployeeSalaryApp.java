package first;

// 抽象类 Employee  
abstract class Employee {
    protected String name;

    public Employee(String name) {
        this.name = name;
    }

    public abstract double printSalary();
}

// 经理类 Manager
class Manager extends Employee {
    private double monthlySalary;

    public Manager(String name, double monthlySalary) {
        super(name);
        this.monthlySalary = monthlySalary;
    }

    public double printSalary() {
        return monthlySalary;
    }
}

// 销售人员类 Salesman
class Salesman extends Employee {
    private double baseSalary;
    private double commission;

    public Salesman(String name, double baseSalary, double commission) {
        super(name);
        this.baseSalary = baseSalary;
        this.commission = commission;
    }

    public double printSalary() {
        return baseSalary + commission;
    }
}

// 工人类 Worker
class Worker extends Employee {
    private double dailyWage;
    private int daysWorked;

    public Worker(String name, double dailyWage, int daysWorked) {
        super(name);
        this.dailyWage = dailyWage;
        this.daysWorked = daysWorked;
    }

    public double printSalary() {
        return dailyWage * daysWorked;
    }
}

// 主类
public class EmployeeSalaryApp {
    public static void main(String[] args) {
        Employee manager = new Manager("何耀慧", 5000);
        Employee salesman = new Salesman("刘婧", 3000, 500);
        Employee worker = new Worker("何不农", 100, 20);

        System.out.println("经理 " + manager.name + " 的工资: " + manager.printSalary());
        System.out.println("销售人员 " + salesman.name + " 的工资: " + salesman.printSalary());
        System.out.println("工人 " + worker.name + " 的工资: " + worker.printSalary());
    }
}