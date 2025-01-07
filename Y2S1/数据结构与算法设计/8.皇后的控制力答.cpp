#include <iostream>

using namespace std;

int m = 0;
int n = 0;
int ans = 0;  
int row[20] = {0};  
int column[20] = {0};  
int slash[50] = {0};  
int reslash[50] = {0};  

int judge()
{  
    for(int i = 1; i <= n; i++) {  
        if(row[i] == 10000) {  
            for(int j = 1; j <= n; j++) {
                if(column[j] == 10000) {  
                    if(!(reslash[i + j] == 1 || slash[n + i - j + 1] == 1)) {  
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void traceback(bool flag, int level, int num)
{  
    if(level > n) {  
        if(num != m)
            return;
        if(judge())
            ans++;
        return;
    }

    if(n - level + num < m)
        return;
    if(!flag) {  
        traceback(false, level + 1, num);
        traceback(true, level + 1, num + 1);
    }
    else {
        for(int i = 1; i <= n; i++) {
            
			if(column[i] == 10000 && reslash[level+i] == 10000 && slash[n+level-i+1] == 10000)
            {
                row[level] = level;  
                column[i] = i;  
                reslash[level + i] = 1;
                slash[n + level - i + 1] = 1;
                traceback(false, level + 1, num);
                traceback(true, level + 1, num + 1);
								// 回溯
                row[level] = 10000;
                column[i] = 10000;
                reslash[level + i] = 10000;
                slash[n + level - i + 1] = 10000;
            }
        }
    }
}

int main()
{
    cin >> n;
    cin >> m;

    for(int i = 0; i <= n; i++) {
        column[i] = 10000;  
        row[i] = 10000;
    }
    for(int i = 0; i < 2 * n + 1; i++) {
        slash[i] = 10000;
        reslash[i] = 10000;
    }

    traceback(false, 1, 0);  
    traceback(true, 1, 1);  
    cout << ans << endl;

    return 0;
}
