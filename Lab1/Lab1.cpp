#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;

// Hàm hỗ trợ trong hàm toán học
bool isNegative(string s);

// Hàm toán học
string f_minus(string s1, string s2);
string f_add(string s1, string s2);
string f_mul(string s1, string s2);
string f_div(string s1, string s2);

// Hàm hỗ trợ 
void deleteBackspace(string &line);
bool isDigit(char c);
bool isOp(string s);
vector<string> getElements(string line);
int priority(string op);
vector<string> makeOrder(string line);

// Hàm xử lý lab1
string process(string line);
void process_file(string input, string output);

/* Usage:
g++ 24120036.cpp -o 24120036
./24120036 tests.txt output_24120036.txt
*/ 
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " input.txt output.txt" << endl;
        return 1;
    }
    process_file(argv[1], argv[2]);
    return 0;
}
bool isNegative(string s) {
    return s[0] == '-';
}

string f_minus(string s1, string s2) {
    string r = "";
    if (isNegative(s1) && isNegative(s2)) {
        s1.erase(0, 1);
        s2.erase(0, 1);
        return f_minus(s2, s1);
    } 
    else if (isNegative(s1) && !isNegative(s2)) {
        s1.erase(0, 1);
        return "-" + f_add(s1, s2);
    } 
    else if (!isNegative(s1) && isNegative(s2)) {
        s2.erase(0, 1);
        return f_add(s1, s2);
    }

    bool negative = false;
    if (s1.length() < s2.length()) {
        string temp = s1;
        s1 = s2;
        s2 = temp;
        negative = true;
    } else if (s1.length() == s2.length()) {
        if (s1 < s2) {
            string temp = s1;
            s1 = s2;
            s2 = temp;
            negative = true;
        }
    }

    int s1_index = s1.length() - 1;
    int s2_index = s2.length() - 1;
    int borrow = 0;

    while (s1_index >= 0 || s2_index >= 0) {
        int s1_digit = 0;
        int s2_digit = 0;

        if (s1_index >= 0) {
            s1_digit = s1[s1_index] - '0';
            s1_index--;
        }
        if (s2_index >= 0) {
            s2_digit = s2[s2_index] - '0';
            s2_index--;
        }
        s1_digit -= borrow;
        if (s1_digit < s2_digit) {
            s1_digit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        int minus_digit = s1_digit - s2_digit;
        char toString_digit = minus_digit + '0';
        r.insert(r.begin(), toString_digit);
    }
    while (r.length() > 1 && r[0] == '0') {
        r.erase(0, 1);
    }
    if (negative) {
        r.insert(r.begin(), '-');
    }
    return r;
}

string f_add(string s1, string s2) {
    string r = "";
    if (isNegative(s1) && isNegative(s2)) {
        s1.erase(0, 1);
        s2.erase(0, 1);
        return r = "-" + f_add(s1, s2);
    }
    else if (isNegative(s1) && !isNegative(s2)) {
        s1.erase(0, 1);
        return r = f_minus(s2, s1);
    }
    else if (!isNegative(s1) && isNegative(s2)) {
        s2.erase(0, 1);
        return r = f_minus(s1, s2);
    }
    else {
        int s1_index = s1.size() - 1;
        int s2_index = s2.size() - 1;
        int bonus = 0;

        while (s1_index >= 0 || s2_index >= 0) {
            int s1_digit = 0;
            if (s1_index >= 0) s1_digit = s1[s1_index--] - '0';
            int s2_digit = 0;
            if (s2_index >= 0) s2_digit = s2[s2_index--] - '0';
            int add_digit = s1_digit + s2_digit + bonus;
            int toString_digit = add_digit % 10;
            bonus = add_digit / 10; 
            r.insert(r.begin(), toString_digit + '0');
        }
    }
    while (r.length() > 1 && r[0] == '0') {
        r.erase(0, 1);
    }
    return r;
}

string f_mul(string s1, string s2) {
    if (s1 == "0" || s2 == "0") return "0";
    string r = "";

    if (isNegative(s1) && isNegative(s2)) {
        s1.erase(0, 1);
        s2.erase(0, 1);
        return f_mul(s1, s2);
    }
    else if (!isNegative(s1) && isNegative(s2)) {
        s2.erase(0, 1);
        r = "-" + f_mul(s1, s2);
        return r;
    }
    else if (isNegative(s1) && !isNegative(s2)) {
        s1.erase(0, 1);
        r = "-" + f_mul(s1, s2);
        return r;
    }

    int s1_index = s1.size() - 1;
    while (s1_index >= 0) {
        int s1_digit = s1[s1_index--] - '0';
        int bonus = 0;
        string temp = "";
    
        for (int i = 0; i < s1.size() - s1_index - 2; i++) {
            temp += '0';
        }

        int s2_index = s2.size() - 1;
        while (s2_index >= 0) {
            int s2_digit = s2[s2_index--] - '0';
            int mul_digit = s1_digit * s2_digit + bonus;
            temp.insert(temp.begin(), (mul_digit % 10) + '0');
            bonus = mul_digit / 10;
        }
    
        if (bonus) {
            temp.insert(temp.begin(), bonus + '0');
        }
        r = f_add(r, temp);
    }
    return r;
}
string f_div(string s1, string s2) {
    string r = "";
    if (s2 == "0") {
        return "ERROR";
    }
    if (s1 == "0") {
        return "0";
    }

    bool negative = false;
    if (isNegative(s1) && isNegative(s2)) {
        s1.erase(0, 1);
        s2.erase(0, 1);
    } else if (isNegative(s1) && !isNegative(s2)) {
        s1.erase(0, 1);
        negative = true;
    } else if (!isNegative(s1) && isNegative(s2)) {
        s2.erase(0, 1);
        negative = true;
    }

    if (s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2)) {
        return "0";
    }

    string current = "";
    int index = 0;
    while (index < s1.size()) {
        current += s1[index];
        while (current.length() > 1 && current[0] == '0') {
            current.erase(0, 1);
        }

        int count = 0;
        while (current.length() > s2.length() || (current.length() == s2.length() && current >= s2)) {
            current = f_minus(current, s2);
            count++;
        }
        r += (count + '0');
        index++;
    }

    while (r.length() > 1 && r[0] == '0') {
        r.erase(0, 1);
    }

    if (negative && r != "0") {
        r.insert(r.begin(), '-');
    }

    return r;
}

void deleteBackspace(string &line) {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
}
bool isOp(string s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "(" || s == ")";
}

bool isDigit(char c) {
    if (c == '0' ||
        c == '1' ||
        c == '2' ||
        c == '3' ||
        c == '4' ||
        c == '5' ||
        c == '6' ||
        c == '7' ||
        c == '8' ||
        c == '9'
    ) {
        return true;
    }
    return false;
}vector<string> getElements(string line) {
    deleteBackspace(line);
    vector<string> r;
    int n = line.size();
    string token = "";

    for (int i = 0; i < n; ++i) {
        char c = line[i];
        if (isDigit(c) || 
            (c == '-' && (i == 0 || line[i - 1] == '(' || isOp(string(1, line[i - 1]))))) {
            token += c;
            i++;
            while (i < n && isDigit(line[i])) {
                token += line[i++];
            }
            i--;
            r.push_back(token);
            token = "";
        }
        else if (isOp(string(1, c))) {
            r.push_back(string(1, c));
        }
    }

    return r;
}

vector<string> makeOrder(string line) {
    vector<string> elements = getElements(line);
    vector<string> order;
    stack<string> ops;
    int n = elements.size();

    for (int i = 0; i < n; i++) {
        string s = elements[i];

        if (!isOp(s)) {
            order.push_back(s);
        }
        else if (s == "(") {
            ops.push(s);
        }
        else if (s == ")") {
            while (!ops.empty() && ops.top() != "(") {
                order.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        }
        else {
            while (!ops.empty() && priority(ops.top()) >= priority(s) && ops.top() != "(") {
                order.push_back(ops.top());
                ops.pop();
            }
            ops.push(s);
        }
    }
    while (!ops.empty()) {
        order.push_back(ops.top());
        ops.pop();
    }
    return order;
}
string process(string line) {
    vector<string> order = makeOrder(line);
    stack<string> workspace;
    for (int i = 0; i < order.size(); i++) {
        if (!isOp(order[i])) {
            workspace.push(order[i]);
        }
        else {
            if (workspace.size() < 2) {
                return "ERROR";
            }
            string s2 = workspace.top();
            workspace.pop();
            string s1 = workspace.top();
            workspace.pop();
            
            if (order[i] == "+") workspace.push(f_add(s1, s2));
            else if (order[i] == "-") workspace.push(f_minus(s1, s2));
            else if (order[i] == "*") workspace.push(f_mul(s1, s2));
            else if (order[i] == "/") {
                string result = f_div(s1, s2);
                if (result.find("ERROR") != string::npos) return result;
                workspace.push(result);
            }
        }
    } 
    if (workspace.empty()) return "ERROR";
    if (workspace.size() != 1) return "ERROR";
    return workspace.top();
}

int priority(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

void process_file(string input, string output) {
    ifstream file(input);
    ofstream out(output);
    if (!file.is_open() || !out.is_open()) {
        cout << "can not open file." << endl;
        return;
    }
    string line;
    while(getline(file, line)) {
        out << process(line);
        out << '\n';
    }
    file.close();
    out.close();
}