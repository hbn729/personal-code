#include <iostream>  
#include <stack>  
#include <string>  
using namespace std;  

// 判断括号是否匹配  
bool isValidBrackets(const string& str) {  
    stack<char> s;  
    for (char ch : str) {  
        if (ch == '(' || ch == '[' || ch == '{') {  
            s.push(ch);  
        } else if (ch == ')' || ch == ']' || ch == '}') {  
            if (s.empty()) return false;  
            char top = s.top();  
            s.pop();   
            if ((ch == ')' && top != '(') ||  
                (ch == ']' && top != '[') ||  
                (ch == '}' && top != '{')) {  
                return false;  
            }  
        }   
    }  
    return s.empty();  
}   

int main() {  
    string expression;  
    cout << "请输入包含括号的字符串: ";  
    getline(cin, expression);  

    if (isValidBrackets(expression)) {  
        cout << "括号匹配正确" << endl;  
    } else {  
        cout << "括号匹配不正确" << endl;  
    }  

    return 0;  
}