#include <iostream>

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
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    int k;
    std::cin >> k;
    std::cout << "Index of K in array: " << linearSearch(a, n, k) << std::endl;
    return 0;
}