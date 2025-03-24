#include <iostream>

using namespace std;

const int N = 5;
int board[N][N] = {0};
int solutions = 0;
// Bài toán n quân hậu
// Hàm kiểm tra vị trí đặt quân có an toàn hay không
bool isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false; // kiểm tra theo cột

        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
            return false; // chéo trái

        if (col + (row - i) < N && board[i][col + (row - i)] == 1)
            return false; // chéo phải
    }
    return true;
}

void solveNQueens(int row)
{
    if (row == N)
    {
        solutions++;
        return;
    }
    for (int col = 0; col < N; col++) // thử các vị trí trên cột
    {
        if (isSafe(row, col))
        {
            board[row][col] = 1; // đạt quân hậu
            solveNQueens(row + 1); // gọi đẹ quy cho dòng tiếp
            board[row][col] = 0; // xóa vị trí vừa đặt để thử các trường hợp khác
        }
    }
}

int main()
{
    solveNQueens(0);
    cout << solutions << std::endl;
    return 0;
}