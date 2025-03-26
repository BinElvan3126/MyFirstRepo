#include <iostream>

int sentinalLinearSearch(int a[], int n, int k)
{
    int last = a[n - 1];
    a[n - 1] = k;

    int i = 0;
    while (a[i] != k)
    {
        i++;
    }

    if (i < n - 1 || a[n - 1] == k)
    {
        return i;
    }
    return -1;
}
int main()
{
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    int k;
    std::cin >> k;
    std::cout << "Index of K in array: " << sentinalLinearSearch(a, n, k) << std::endl;
    return 0;
}