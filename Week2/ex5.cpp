#include <iostream>

using namespace std;

int minLength(int a[], int n, int tg) 
{
    int del = 0, sum = 0, min = n + 1;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        while (sum >= tg) {
            min--;
            sum -= a[del++];
        }
    }
    return min;
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

    int tg;
    cin >> tg;

    cout << minLength(a, n, tg);
    return 0;
}