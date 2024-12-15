package second.task2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class task2 extends JFrame {

    public task2() {
        setTitle("实验任务2");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        JMenu fileMenu = new JMenu("File");
        menuBar.add(fileMenu);

        JMenu formatMenu = new JMenu("Format");
        menuBar.add(formatMenu);

        JMenuItem chineseItem = new JMenuItem("中文");
        formatMenu.add(chineseItem);

        JMenu radixMenu = new JMenu("进制");
        formatMenu.add(radixMenu);

        JMenuItem binaryItem = new JMenuItem("二进制");
        radixMenu.add(binaryItem);

        JMenuItem octalItem = new JMenuItem("八进制");
        radixMenu.add(octalItem);

        JMenuItem decimalItem = new JMenuItem("十进制");
        radixMenu.add(decimalItem);

        JMenu helpMenu = new JMenu("Help");
        menuBar.add(helpMenu);

        chineseItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("中文");
            }
        });

        binaryItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("二进制");
            }
        });
        octalItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("八进制");
            }
        });
        decimalItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("十进制");
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        new task2();
    }
}
