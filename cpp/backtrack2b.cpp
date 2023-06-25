#include "head.hpp"

class Solution {

public:
    /* 输入棋盘边长 n，函数找到一个答案后就返回 true */
    vector<vector<string>> solveNQueens(int n) {
        // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }

private:
    vector<vector<string>> res;

    /* 是否可以在 board[row][col] 放置皇后？ */
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        // 检查列是否有皇后互相冲突
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q')
                return false;
        }
        // 检查右上方是否有皇后互相冲突
        for (int i = row - 1, j = col + 1; 
                i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }
        // 检查左上方是否有皇后互相冲突
        for (int i = row - 1, j = col - 1;
                i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }
        return true;
    }

    // 路径：board 中小于 row 的那些行都已经成功放置了皇后
    // 选择列表：第 row 行的所有列都是放置皇后的选择
    // 结束条件：row 超过 board 的最后一行
    bool backtrack(vector<string>& board, int row) {
        // 触发结束条件
        if (row == board.size()) {
            res.push_back(board);
            return true;
        }

        int n = board[row].size();
        for (int col = 0; col < n; col++) {
            // 排除不合法选择
            if (!isValid(board, row, col)) 
                continue;
            // 做选择
            board[row][col] = 'Q';
            // 进入下一行决策
            if(backtrack(board, row + 1)) 
                return true;
            // 撤销选择
            board[row][col] = '.';
        }
        return false;
    }

};

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line = "8";
    int k = stringToInteger(line);
    vector<vector<string>> rets = Solution().solveNQueens(k);
    int num = 1;
    for(auto ret:rets)
    {   
        cout<<"----sln"<<num<<"----"<<endl;
        for(auto r:ret){
            cout <<r<<endl;
        }
        cout<<"----end"<<num<<"----"<<endl;
        num ++;
    }
    return 0;
}

