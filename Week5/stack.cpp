#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack() {
    Stack* stack = new Stack;
    stack->top = nullptr;
    return stack;
}

void push(Stack* stack, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (stack->top == nullptr) {
        return -1;
    }
    NODE* temp = stack->top;
    int data = temp->key;
    stack->top = stack->top->p_next;
    delete temp;
    return data;
}

bool isEmpty(Stack* stack) {
    return stack->top == nullptr;
}

string printStackToString(Stack* stack) {
    string s;
    NODE* cur = stack->top;
    while (cur != nullptr) {
        s += to_string(cur->key) + " ";
        cur = cur->p_next;
    }
    return s;
}

void check(const string& s, Stack* st, ofstream& outFile) {
    if (s == "init") {
        if (isEmpty(st)) outFile << "EMPTY\n";
        else outFile << printStackToString(st) << "\n";
    }
    else if (s.find("push") != string::npos) {
        size_t pos = s.find("push") + 4;
        int value = stoi(s.substr(pos));
        push(st, value);
        outFile << printStackToString(st) << "\n";
    }
    else if (s == "pop") {
        pop(st);
        if (isEmpty(st)) outFile << "EMPTY\n";
        else outFile << printStackToString(st) << "\n";
    }
}

void readFromFile(const string& input, const string& output, Stack* st) {
    ifstream inFile(input);
    ofstream outFile(output);
    
    if (!inFile.is_open()) {
        cout << "Can't open " << input << endl;
        return;
    }
    if (!outFile.is_open()) {
        cout << "Can't open " << output << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        check(line, st, outFile);
    }

    inFile.close();
    outFile.close();
}

int main() {
    string in = "input.txt";
    string out = "output.txt";
    Stack* st = initializeStack();
    readFromFile(in, out, st); 
    return 0;  
}
