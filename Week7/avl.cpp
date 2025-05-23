#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
NODE* createNode(int data) {
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    newNode->height = 1;
    return newNode;
}
int height(NODE* pNode) {
    if (pNode == nullptr) return 0;
    return pNode->height;
}
int balance(NODE* pNode) {
    if (pNode == nullptr) return 0;
    return height(pNode->p_left) - height(pNode->p_right);
}
NODE* rightRotate(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    y->height = 1 + max(height(y->p_left), height(y->p_right));
    x->height = 1 + max(height(x->p_left), height(x->p_right));
    return x;
}
NODE* leftRotate(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    x->height = 1 + max(height(x->p_left), height(x->p_right));
    y->height = 1 + max(height(y->p_left), height(y->p_right));
    return y;
}
void Insert(NODE*& pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    } else {
        return;
    }
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    int bf = balance(pRoot);

    if (bf > 1 && x < pRoot->p_left->key) {
        pRoot = rightRotate(pRoot);
    }
    if (bf < -1 && x > pRoot->p_right->key) {
        pRoot = leftRotate(pRoot);
    }
    if (bf > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    if (bf < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

NODE* nodeMin(NODE* node) {
    NODE* cur = node;
    while (cur->p_left != nullptr) {
        cur = cur->p_left;
    }
    return cur;
}

void Remove(NODE*& pRoot, int x) {
    if (pRoot == nullptr) return;
    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
                delete pRoot;
                pRoot = nullptr;
            } else if (pRoot->p_left == nullptr) {
                NODE* temp = pRoot;
                pRoot = pRoot->p_right;
                delete temp;
            } else if (pRoot->p_right == nullptr) {
                NODE* temp = pRoot;
                pRoot = pRoot->p_left;
                delete temp;
            }
        } else {
            NODE* temp = nodeMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    if (pRoot == nullptr) return;
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));

    int bf = balance(pRoot);
    if (bf > 1 && balance(pRoot->p_left) >= 0) {
        pRoot = rightRotate(pRoot);
    }
    if (bf > 1 && balance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    if (bf < -1 && balance(pRoot->p_right) <= 0) {
        pRoot = leftRotate(pRoot);
    }
    if (bf < -1 && balance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}
bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr) return true;
    int bf = balance(pRoot);
    if (bf > 1 || bf < -1) return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
// int main() {
//     NODE* root = nullptr;
//     Insert(root, 10);
//     Insert(root, 20);
//     Insert(root, 30);
//     Insert(root, 40);
//     Insert(root, 50);
//     Insert(root, 25);
//     cout << isAVL(root) << endl;
//     Remove(root, 40);
//     cout << isAVL(root) << endl;

//     return 0;
// }