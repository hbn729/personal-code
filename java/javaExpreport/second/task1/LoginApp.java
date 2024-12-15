package second.task1;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    public static void main(String[] args) {
        JFrame frame = new JFrame("登录");
        LoginPanel loginPanel = new LoginPanel();
        frame.add(loginPanel);
        frame.setSize(300, 150);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}

class LoginPanel extends JPanel {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton confirmButton;

    public LoginPanel() {
        setLayout(new GridLayout(3, 2, 10, 10));

        JLabel userLabel = new JLabel("用户名:");
        usernameField = new JTextField(10);

        JLabel passwordLabel = new JLabel("密码:");
        passwordField = new JPasswordField(10);
        passwordField.setEchoChar('*'); // 隐藏密码显示

        confirmButton = new JButton("确定");

        add(userLabel);
        add(usernameField);
        add(passwordLabel);
        add(passwordField);
        add(new JLabel()); // 占位使按钮居中
        add(confirmButton);

        confirmButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 打印输入的用户名和密码（实际应验证）
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();
                System.out.println("用户名: " + username);
                System.out.println("密码: " + new String(password)); // 实际不应打印密码
            }
        });
    }
}