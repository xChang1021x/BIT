#include"methods.h"

// Solution��Ĺ��캯������ʼ��������Ĵ�СΪ9x9��
Solution::Solution() {
    this->board.resize(9); // ����board��һ��vector<vector<char>>���͵ĳ�Ա������
}

// ������������(x, y)λ�÷�������k�Ƿ���Ч��
bool Solution::isValid(int x, int y, char k, vector<string>& board) {
    // ��鵱ǰ���Ƿ��Ѵ���k
    for (int i = 0; i < y; ++i) {
        if (board[x][i] == k) return false;
    }
    // ��鵱ǰ���Ƿ��Ѵ���k
    for (int i = y + 1; i < 9; ++i) {
        if (board[x][i] == k) return false;
    }
    // ��鵱ǰ���Ƿ��Ѵ���k
    for (int i = 0; i < x; ++i) {
        if (board[i][y] == k) return false;
    }
    // ��鵱ǰ���Ƿ��Ѵ���k
    for (int i = x + 1; i < 9; ++i) {
        if (board[i][y] == k) return false;
    }
    // ���3x3�ӹ��Ƿ��Ѵ���k
    for (int i = x / 3 * 3; i <= x / 3 * 3 + 2; ++i) {
        for (int j = y / 3 * 3; j <= y / 3 * 3 + 2; ++j) {
            if (board[i][j] == k) return false;
        }
    }
    return true; // ������϶�����ͻ���򷵻�true��
}

// ʹ�û��ݷ����Խ���������⡣
bool Solution::bt(vector<string>& board) {
    for (int i = 0; i < 9; ++i) { // �����������ÿһ��
        for (int j = 0; j < 9; ++j) { // �����������ÿһ��
            if (board[i][j] == '.') { // �����ǰλ���ǿյģ�δ�������֣�
                for (char k = '1'; k <= '9'; ++k) { // ��������1��9������
                    if (isValid(i, j, k, board)) { // �������k����Ч��
                        board[i][j] = k; // ��������k
                        if (bt(board)) return true; // �ݹ����bt���Խ��ʣ���������
                        board[i][j] = '.'; // ������ǽ⣬���ݣ�����ǰλ������Ϊ��
                    }
                }
                return false; // ���û�����ֿ������룬˵�������޽�
            }
        }
    }
    return true; // �������λ�ö����������֣�˵�������Ѿ����
}

// ����������Ⲣ��ӡ������ӡ�޽���Ϣ��
void Solution::solveSudoku(vector<string>& board) {
    if (bt(board)) { // ������ݷ��ҵ���
        // ��ӡ�����壬��ʽ�����
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << board[i][j];
                if (j == 2 || j == 5) cout << "  "; // ��ӡÿ3�����ֺ���ӿո�
            }
            if (i == 2 || i == 5) cout << endl; // ��ӡÿ3�к���
            cout << endl;
        }
    }
    else {
        printf("�������޽⣡����"); // ��������޽�
    }
}

// ��ӡ��������Ҫ��
void Solution::print() {
    cout << "-----9*9 �����ƽ���-----" << endl;
    cout << "����Ҫ��" << endl;
    cout << "1. �հ׵ط���'.'�Ŵ��棨�������ţ�" << endl;
    cout << "2. ���ո����������Ÿ�����Ȼ��س����ظ��˲���" << endl;
    cout << endl << endl << "����ʼ�����" << endl;
}