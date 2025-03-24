#include <iostream>
using namespace std;

void fibonacci(int n, int a = 0, int b = 1) 
{
    if (n > 0) {
        cout << a << " ";
        fibonacci(n - 1, b, a + b);
    }
    // Sử dụng tham số a và b để khởi tạo dã fibonacci
}

int main()
{
    fibonacci(0);
    cout << endl;
    fibonacci(1);
    cout << endl;
    fibonacci(5);
    return 0;
}