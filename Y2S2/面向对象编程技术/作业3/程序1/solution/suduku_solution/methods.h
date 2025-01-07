#include<vector>
#include<string>
#include<iostream>
using namespace std;

#pragma once
#ifndef _METHODS_H_
#define _METHODS_H_

class Solution {
public:
    vector<string> board;

    Solution();
    bool isValid(int x, int y, char k, vector<string>& board);
    bool bt(vector<string>& board);
    void print();
    void solveSudoku(vector<string>& board);
};

#endif