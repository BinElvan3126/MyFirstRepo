#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue() {
    Queue* queue = new Queue;
    queue->head = nullptr;
    queue->tail = nullptr;
    return queue;
}

void enqueue(Queue* queue, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = nullptr;
    if (queue->tail == nullptr) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->p_next = newNode;
        queue->tail = newNode;
    }
}

int dequeue(Queue* queue) {
    if (queue->head == nullptr) {
        return -1;
    }
    NODE* temp = queue->head;
    int data = temp->key;
    queue->head = queue->head->p_next;
    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
    delete temp;
    return data;
}

bool isEmpty(Queue* queue) {
    return queue->head == nullptr;
}

string printQueueToString(Queue* queue) {
    string result;
    NODE* cur = queue->head;
    while (cur != nullptr) {
        result += to_string(cur->key) + " ";
        cur = cur->p_next;
    }
    return result;
}

void check(const string& command, Queue* q, ofstream& outFile) {
    if (command == "init") {
        if (isEmpty(q)) outFile << "EMPTY\n";
        else outFile << printQueueToString(q) << "\n";
    } 
    else if (command.find("enqueue") != string::npos) {
        size_t pos = command.find("enqueue") + 7;
        int value = stoi(command.substr(pos));
        enqueue(q, value);
        outFile << printQueueToString(q) << "\n";
    } 
    else if (command == "dequeue") {
        dequeue(q);
        if (isEmpty(q)) outFile << "EMPTY\n";
        else outFile << printQueueToString(q) << "\n";
    }
}

void readFromFile(const string& input, const string& output, Queue* q) {
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
        check(line, q, outFile);
    }

    inFile.close();
    outFile.close();
}

int main() {
    string in = "input.txt";
    string out = "output.txt";
    Queue* q = initializeQueue();
    readFromFile(in, out, q);
    return 0;
}
