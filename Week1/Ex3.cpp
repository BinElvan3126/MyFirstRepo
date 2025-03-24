#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) 
{
    // Nếu độ dài chuỗi hiện tại bằng n
    if (n == str.size()) 
    {
        cout << str << endl;
        return;
    }
    
    // Gọi đệ quy thêm '0' vào chuỗi hiện tại
    // Nhánh 0
    generateBinaryStrings(n, str + "0");
    
    // Gọi đệ quy thêm '1' vào chuỗi hiện tại
    // Nhánh 1
    generateBinaryStrings(n, str + "1");
}

int main() 
{
    string s;
    generateBinaryStrings(3, s);
    return 0;
}