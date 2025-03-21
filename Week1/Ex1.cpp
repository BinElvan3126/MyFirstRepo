#include <iostream>

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void fibonacciSeries(int n)
{
    std::cout << n << std::endl;
    for (
        int i = 0;
        i < n;
        i++)
    {
        std::cout << fibonacci(i) << " ";
    }
}
int main()
{
    fibonacciSeries(5);
    return 0;
}