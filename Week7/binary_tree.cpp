#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct NODE{
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
vector<int> NLR(NODE* root) {
	vector<int> store;
	if(root == nullptr) return store;
	store.push_back(root->key);
	vector<int> subLeft = NLR(root->p_left);
	store.insert(store.end(), subLeft.begin(), subLeft.end());
	vector<int> subRight = NLR(root->p_right);
	store.insert(store.end(), subRight.begin(), subRight.end());
	return store;
}
vector<int> LNR(NODE* root) {
	vector<int> store;
	if(root != nullptr) {
		vector<int> subLeft = LNR(root->p_left);
		store.insert(store.end(), subLeft.begin(), subLeft.end());
		store.push_back(root->key);
		vector<int> subRight = LNR(root->p_right);
        store.insert(store.end(), subRight.begin(), subRight.end());
	}
	return store;
}
vector<int> LRN(NODE* root) {
	vector<int> store;
	if(root == nullptr) return store;
	vector<int> subLeft = NLR(root->p_left);
	store.insert(store.end(), subLeft.begin(), subLeft.end());
	vector<int> subRight = NLR(root->p_right);
	store.insert(store.end(), subRight.begin(), subRight.end());
	store.push_back(root->key);
	return store;
}
void levelOrder_suppport(NODE* root, int level, vector<vector<int>>& res) {
    if (root == nullptr) return;
    if (res.size() <= level) res.push_back({});
    res[level].push_back(root->key);

    levelOrder_suppport(root->p_left, level + 1, res);
    levelOrder_suppport(root->p_right, level + 1, res);
}
vector<vector<int>> levelOrder(NODE* root) {
    vector<vector<int>> store; 
    levelOrder_suppport(root, 0, store);
    return store;
}
int countNode(NODE* root) {
	if(root == nullptr) return 0;
	int l = countNode(root->p_left);
	int r = countNode(root->p_right);
	return l + r + 1;
}
int sumNode(NODE* root) {
	if(root == nullptr) return 0;
	int l = sumNode(root->p_left);
	int r = sumNode(root->p_right);
	return l + r + root->key;
}
int height(NODE* root) {
	if (root == nullptr) return -1;
	int l = height(root->p_left);
	int r = height(root->p_right);
	return max(l, r) + 1;
}
int heightNode(NODE* root, int value) {
    if (root == nullptr) return -1;
    if (root->key == value) {
        return height(root);
    }
    int l = heightNode(root->p_left, value);
    if (l != -1) return l;
    int r = heightNode(root->p_right, value);
    if (r != -1) return r;
	return -1;
}
int Level(NODE* root, NODE* p) {
	if (root == nullptr || p == nullptr) return -1;
	if (root == p) return 0;
	int l = Level(root->p_left, p);
	if (l != -1) return l + 1;
	int r = Level(root->p_right, p);
	if (r != -1) return r + 1;
	return -1;
}
int countLeaf(NODE* root) {
	if (root == nullptr) return -1;
	if (root->p_left == nullptr && root->p_right == nullptr) return 1;
	int l = countLeaf(root->p_left);
	int r = countLeaf(root->p_right);
	return l + r;
}
int main() {
	NODE* root = createNode(40);
    root->p_left = createNode(20);
    root->p_right = createNode(60);
    root->p_left->p_left = createNode(10);
    root->p_left->p_right = createNode(30);
    root->p_right->p_left = createNode(50);
    root->p_right->p_right = createNode(70);
	cout << countLeaf(root) << endl;
	return 0;
}
