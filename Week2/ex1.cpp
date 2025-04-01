#include <iostream>

using namespace std;

int linearSearch(int a[], int n, int k)
{
    int idx;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == k)
            return i;
    }
    return -1;
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
    cout << "Index of K in array: " << linearSearch(a, n, k) << endl;
    return 0;
}