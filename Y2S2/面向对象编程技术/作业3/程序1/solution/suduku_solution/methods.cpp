#include"methods.h"

// Solution类的构造函数，初始化数独板的大小为9x9。
Solution::Solution() {
    this->board.resize(9); // 假设board是一个vector<vector<char>>类型的成员变量。
}

// 检查在数独板的(x, y)位置放置数字k是否有效。
bool Solution::isValid(int x, int y, char k, vector<string>& board) {
    // 检查当前列是否已存在k
    for (int i = 0; i < y; ++i) {
        if (board[x][i] == k) return false;
    }
    // 检查当前行是否已存在k
    for (int i = y + 1; i < 9; ++i) {
        if (board[x][i] == k) return false;
    }
    // 检查当前列是否已存在k
    for (int i = 0; i < x; ++i) {
        if (board[i][y] == k) return false;
    }
    // 检查当前行是否已存在k
    for (int i = x + 1; i < 9; ++i) {
        if (board[i][y] == k) return false;
    }
    // 检查3x3子宫是否已存在k
    for (int i = x / 3 * 3; i <= x / 3 * 3 + 2; ++i) {
        for (int j = y / 3 * 3; j <= y / 3 * 3 + 2; ++j) {
            if (board[i][j] == k) return false;
        }
    }
    return true; // 如果以上都不冲突，则返回true。
}

// 使用回溯法尝试解决数独问题。
bool Solution::bt(vector<string>& board) {
    for (int i = 0; i < 9; ++i) { // 遍历数独板的每一行
        for (int j = 0; j < 9; ++j) { // 遍历数独板的每一列
            if (board[i][j] == '.') { // 如果当前位置是空的（未填入数字）
                for (char k = '1'; k <= '9'; ++k) { // 尝试填入1到9的数字
                    if (isValid(i, j, k, board)) { // 如果填入k是有效的
                        board[i][j] = k; // 填入数字k
                        if (bt(board)) return true; // 递归调用bt尝试解决剩余的数独板
                        board[i][j] = '.'; // 如果不是解，回溯，将当前位置重置为空
                    }
                }
                return false; // 如果没有数字可以填入，说明数独无解
            }
        }
    }
    return true; // 如果所有位置都填入了数字，说明数独已经解决
}

// 解决数独问题并打印结果或打印无解消息。
void Solution::solveSudoku(vector<string>& board) {
    if (bt(board)) { // 如果回溯法找到解
        // 打印数独板，格式化输出
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << board[i][j];
                if (j == 2 || j == 5) cout << "  "; // 打印每3个数字后添加空格
            }
            if (i == 2 || i == 5) cout << endl; // 打印每3行后换行
            cout << endl;
        }
    }
    else {
        printf("此数独无解！！！"); // 如果数独无解
    }
}

// 打印数独输入要求
void Solution::print() {
    cout << "-----9*9 数独破解器-----" << endl;
    cout << "输入要求：" << endl;
    cout << "1. 空白地方用'.'号代替（忽略引号）" << endl;
    cout << "2. 不空格的连续输入九个数，然后回车，重复此操作" << endl;
    cout << endl << endl << "↓开始输入↓" << endl;
}