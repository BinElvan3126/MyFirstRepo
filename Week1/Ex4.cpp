#include <iostream>
using namespace std;

void tower(int n, char from_rod, char to_rod, char aux_rod) 
{
    if (n == 1) {
        cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
        return;
    }

    tower(n - 1, from_rod, aux_rod, to_rod); // chuyển đến nơi trung giang
    cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
    tower(n - 1, aux_rod, to_rod, from_rod); // lấy về lại
}
int main() 
{ 
    int n;
    cin >> n;
    tower(n, 'A', 'B', 'C');
    return 0;
}