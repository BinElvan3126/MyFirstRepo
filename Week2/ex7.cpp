#include <iostream>

using namespace std;

void sort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void zeroSumOfThree(int a[], int n) 
{
    bool isFirst = true;
    cout << "[";
    sort(a, n);
    if (a[0] >= 0) {
        cout << "]";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] == a[i-1]) continue;
        int low = i + 1, high = n - 1;
        while (low < high) {
            int sum = a[low] + a[i] + a[high];
            if (sum == 0) {
                if (!isFirst) {
                    cout << ", ";
                }
                cout << "[" << a[i] << ", " << a[low] << ", " << a[high] << "]";
                isFirst = false;
                low++;
                high--;
            }
            else if (sum < 0) low++;
            else high--;
        }
    }
    cout << "]";


}
int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    zeroSumOfThree(a, n);
    return 0;
}