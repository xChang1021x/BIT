#include"methods.h"

int main() {
    Solution temp = Solution();

    temp.print();
    
    for (int i = 0; i < 9; ++i) {
        cin >> temp.board[i];
    }
    temp.solveSudoku(temp.board);
    return 0;
}