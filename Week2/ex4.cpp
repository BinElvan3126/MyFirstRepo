#include <iostream>

using namespace std;

bool canShip(int w[], int n, int cap, int day) {
    int sum = 0, d = 1;
    for (int i = 0; i < n; i++) {
        if (sum + w[i] > cap) {
            d++;
            sum = 0;
        }
        sum += w[i];
    }
    return d <= day;
}

int minCapacity(int w[], int n, int day) {
    int min = 0, cap = 0;
    for (int i = 0; i < n; i++) {
        min = max(min, w[i]);
        cap += w[i];
    }
    while (min < cap) {
        int mid_w = (min + cap) / 2;
        if (canShip(w, n, mid_w, day)) cap = mid_w;
        else min = mid_w + 1;
    }
    return min;
}

int main() {
    int n, day;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> day;
    cout << minCapacity(a, n, day) << endl;
    return 0;
}
