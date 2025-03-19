#include <iostream>

void generateBinaryStrings(int n, std::string str)
{
    if (n == str.size())
    {
        std::cout << str << std::endl;
        return;
    }
    generateBinaryStrings(n, str + "0");
    generateBinaryStrings(n, str + "1");
}
int main()
{
    std::string s;
    generateBinaryStrings(3, s);
    return 0;
}
