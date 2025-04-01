#include <iostream>

using namespace std;

bool isExist(int a[], int n, int k) {
    int left = 0, right = n - 1;
    while (left < right) {
        if (a[left] > k) break;
        int sum = a[left] + a[right];
        if (sum == k) return true;
        else if (sum < k) left++;
        else right--;
    }
    return false;
}
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int k;
    cin >> k;

    if(isExist(a, n, k)) cout << "YES";
    else cout << "NO";
    return 0;
}