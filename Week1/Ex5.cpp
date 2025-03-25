#include <iostream>
using namespace std;
bool isSorted(int arr[], int n) 
{
    if (n == 1 || n == 0)
        return true;

    if (arr[0] > arr[1])
        return false;

    return isSorted(arr + 1, n - 1); // Arr + 1 : tăng theo kiểu pointer
    /*
    Tăng index của arr bằng cách gọi đệ quy 
    Tiếp tục kiểm tra giá trị bool của hàm sau khi gọi đệ quy
    */
}

int main() 
{
    int n;
    cin >> n;
    int arr[n] = {}; 
    for (int i = 0; i< n; i++) {
        cin >> arr[i];
    }

    if (isSorted(arr, n))
        cout << "The array is sorted.\n";
    else
        cout << "The array is NOT sorted.\n";

    return 0;
}