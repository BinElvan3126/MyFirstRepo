#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};
NODE* createNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}
NODE* Search(NODE* root, int x) {
    if (root == nullptr || root->key == x) {
        return root;
    }
    if (x < root->key) {
        return Search(root->p_left, x);
    } else {
        return Search(root->p_right, x);
    }
}
void Insert(NODE* &root, int x) {
    if (root == nullptr) {
        root = createNode(x);
        return;
    }
    if (x < root->key) {
        Insert(root->p_left, x);
    } else if (x > root->key) {
        Insert(root->p_right, x);
    }
}
NODE* mostLeft(NODE* root) {
    while (root != nullptr && root->p_left != nullptr) {
        root = root->p_left;
    }
    return root;
}
NODE* mostRight(NODE* root) {
    while (root != nullptr && root->p_right != nullptr) {
        root = root->p_right;
    }
    return root;
}
void Remove(NODE* &root, int x) {
    if (root == nullptr ) return;
    if (x < root->key) {
        Remove(root->p_left, x);
    }else if (x > root->key) {
        Remove(root->p_right, x);
    }else {
        if (root->p_left == nullptr) {
            NODE* temp = root->p_right;
            delete root;
            root = temp;
        }else if (root->p_right == nullptr) {
            NODE* temp = root->p_left;
            delete root;
            root = temp;
        }else {
            NODE* temp = mostLeft(root->p_right);
            root->key = temp->key;
            Remove(root->p_right, temp->key);
        }
    }
}
NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; i++) {
        Insert(root, a[i]);
    }
    return root;
}
void removeTree(NODE* &root) {
    if (root == nullptr) return;
    removeTree(root->p_left);
    removeTree(root->p_right);
    delete root;
    root = nullptr;
}
int Height(NODE* root) {
    if (root == nullptr) return -1;
	int l = Height(root->p_left);
	int r = Height(root->p_right);
	return max(l, r) + 1;
}
void ino(NODE* root) {
    if (root == nullptr) {
        return;
    }
    ino(root->p_left);
    cout << root->key << " ";
    ino(root->p_right);
}
int countLess(NODE* root, int x) {
    if (root == nullptr) return 0;
    if(root->key < x) {
        return 1 + countLess(root->p_left, x) + countLess(root->p_right, x);
    }else {
        return countLess(root->p_left, x);
    }
}
int countGreater(NODE* root, int x) {
    if (root == nullptr) return 0;
    if(root->key > x) {
        return 1 + countGreater(root->p_left, x) + countGreater(root->p_right, x);
    }else {
        return countGreater(root->p_right, x);
    }
}
bool checkOrder(NODE* root, int &last_key) {
    if (root == nullptr) return true;
    if (!checkOrder(root->p_left, last_key)) {
        return false;
    }
    if (last_key >= root->key) {
        return false;
    }
    last_key = root->key;
    return checkOrder(root->p_right, last_key);
}
bool isBST(NODE* root) {
    int last_key = INT_MIN;
    return checkOrder(root, last_key);
}
bool isFullBST(NODE* root) {
    if (!isBST(root)) return false;
    if (root == nullptr) return true;
    if (root->p_left == nullptr && root->p_right == nullptr) {
        return true;
    }
    if (root->p_left != nullptr && root->p_right != nullptr) {
        return isFullBST(root->p_left) && isFullBST(root->p_right);
    }
    return false;
}
// int main() {
//     int a[] = {50,40,60,30,45,70,47,80,75,90,74, 76,44, 59, 69};
//     int n = sizeof(a) / sizeof(a[0]);
//     NODE* root = nullptr;
//     root = createTree(a, n);
//     ino(root);
//     cout << "\n";
//     cout << isFullBST(root) << endl;
// }