// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 100> stack;
    std::map<char, int> priority;
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.isEmpty()) stack.pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && stack.top() != '(' && 
                   priority[stack.top()] >= priority[c]) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }
    
    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }
    
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    
    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        
        if (isdigit(c)) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            stack.push(num);
            --i;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = stack.pop();
            int a = stack.pop();
            int res = 0;
            
            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/') res = a / b;
            
            stack.push(res);
        }
    }
    
    return stack.pop();
}
