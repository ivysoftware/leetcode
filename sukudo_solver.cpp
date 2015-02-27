#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    vector< vector< set<int> > > board_queue;
    stack<int> path;
    stack<set<int> > ori;
    bool FillPiece(int x,  int y){
        bool has_fill = false;
        int gi= x / 3, gj= y / 3, t, li,lj,missing_count = 0,missing_value = -1;
        set<int> values;
        for(t = 0 ; t < 9; t ++) values.insert(t);
        for(t = 0; t < 9; t ++){
            if(board_queue[x][t].size() == 1 && values.count(*(board_queue[x][t].begin())) > 0) values.erase(*(board_queue[x][t].begin()));
			if(board_queue[t][y].size() == 1 && values.count(*(board_queue[t][y].begin())) > 0) values.erase(*(board_queue[t][y].begin()));
            li = gi * 3 + t / 3; lj = gj * 3 + t % 3;
            if(board_queue[li][lj].size() == 1 && values.count(*(board_queue[li][lj].begin())) > 0) values.erase(*(board_queue[li][lj].begin()));
        }
        board_queue[x][y].clear();
        set<int>::iterator it = values.begin();
        for(; it != values.end(); it ++) board_queue[x][y].insert(*(it));
        if(values.size() == 1) has_fill = true; 
        return has_fill;
    }    
    bool FillBoardQueue(vector<vector<char> > &board){
        bool has_blank = false;
        int i,j,t,gi,gj, li, lj ;
        board_queue.clear();  board_queue.resize(9);
        //填充候选位置，如果确定只有一个，则第三维长度为1
        for(i = 0; i < 9; i ++){
            board_queue[i].resize(9);
            for(j = 0; j < 9; j ++){
                if(board[i][j] != '.') board_queue[i][j].insert(board[i][j] - '1');
                else has_blank = true;
            }
        }
        return has_blank;
    }
    bool Sweep(int x, int y, int target){
        if(board_queue[x][y].size() > 1 && board_queue[x][y].count(target) > 0){
            path.push(x * 10 + y); ori.push(board_queue[x][y]);  
            board_queue[x][y].erase(target);
            if(board_queue[x][y].size() == 1){
                int t = *(board_queue[x][y].begin());
                if(!SweepRow(x, y, t) || !SweepCol(x, y, t) || !SweepGroup(x, y, t)){
                    while(path.top() != x * 10 + y){
                        board_queue[path.top() / 10][path.top() % 10] = ori.top(); path.pop(); ori.pop();
                    }
                    board_queue[x][y] = ori.top(); path.pop(); ori.pop();   
                    return false;
                } 
            }
        }
        else if(board_queue[x][y].size() == 1 && board_queue[x][y].count(target) > 0){
            return false;
        }
        return true;
    }
    bool SweepRow(int x, int y, int target){
        for(int j = 0; j < 9; j ++){
        	if(j == y) continue;
            if(!Sweep(x, j, target)) return false;
        }
        return true;
    }
    bool SweepCol(int x, int y, int target){
        for(int i = 0; i < 9; i ++){
        	if(i == x) continue;
            if(!Sweep(i, y, target)) return false;
        }
        return true;
    }
    bool SweepGroup(int x, int y, int target){
        int gi = x / 3; int gj = y / 3; int lx, ly, t;
        for(int i = 0; i < 3; i ++){
            for(int j = 0 ; j < 3; j ++){
                lx = gi * 3 + i; ly = gj * 3 + j;
                if(x == lx && y == ly) continue;
                if(!Sweep(lx, ly, target)) return false;
            }
        }
        return true;
    }

    bool FillItem()
    {
        bool has_fill_one = false;
        int i,j,t;
        for(i = 0; i < 9; i ++){
            for(j = 0; j < 9; j ++){
                if(board_queue[i][j].size() != 1 && FillPiece(i, j) == true){//确定能填充一个
                    t = *(board_queue[i][j].begin()); 
                    SweepRow(i, j, t) ; SweepCol(i, j, t); SweepGroup(i, j, t);                       
                    has_fill_one = true;
                }
            }
        }
        return has_fill_one;
    }
    bool ChooseMin(int &x, int &y)
	{
		bool has_min = false;
		int min_count = 9;
		x = y = -1;
        for(int i = 0; i < 9; i ++){
            for(int j = 0; j < 9; j++){
            	if(board_queue[i][j].size() > 1 && board_queue[i][j].size() < min_count){
            		min_count = board_queue[i][j].size();
            		x = i; y = j;
            	}
            }
		}
		if(x != -1 && y != -1) has_min = true;
		return has_min; 
	} 
    bool GuessItem()
    {
        bool has_guessok = false, back = false;
        int x , y, lx, ly, g_value, l_value;
        stack<int> choose;
        while(path.size() > 0) {path.pop(); ori.pop();}      
        do{
            x = y = -1;
            if(!ChooseMin(x, y)) {has_guessok = true; break;}
            path.push(x* 10 + y); ori.push(board_queue[x][y]); choose.push(x*10 + y);
			board_queue[x][y].clear();
            g_value = *(ori.top().begin());
            board_queue[x][y].insert(g_value);   
            while(back || 
            (board_queue[x][y].size() == 1 && (
            !SweepRow(x, y, *(board_queue[x][y].begin())) || 
            !SweepCol(x, y, *(board_queue[x][y].begin())) || 
            !SweepGroup(x, y,*(board_queue[x][y].begin()))))){//2. 失败（当前格后选值个数为0），退堆栈,清除该错误选择
                back = false;
                l_value = *(board_queue[x][y].begin());
                while(path.size() > 0 && path.top() != choose.top()){
                    board_queue[path.top() / 10][path.top() % 10] = ori.top();
                    path.pop(); ori.pop();
                }
                x = path.top() / 10; y = path.top() % 10;
                board_queue[x][y] = ori.top();
                board_queue[x][y].erase(l_value);
                if(board_queue[x][y].size() == 1){
                    path.push(x* 10 + y); ori.push(board_queue[x][y]);}
                else if(board_queue[path.top() / 10][path.top() % 10].size() == 0){//无可选，后退一步,到不同的选择点上
                    back = true;
                    while(path.top() == choose.top()) choose.pop();
                    x = choose.top() / 10; y = choose.top() % 10;
                }
                else{
                    l_value = *(board_queue[x][y].begin());
                    path.push(x* 10 + y); ori.push(board_queue[x][y]);
                    board_queue[x][y].clear();
                    board_queue[x][y].insert(l_value);                    
                }
            }  
        }while(choose.size() > 0);//3. 成功，则继续选择可能性最少的一个
        return has_guessok;
    }
  	void FillBoard(vector<vector<char> > &board)
  	{
        for(int i = 0; i < 9; i ++)
            for(int j = 0; j < 9; j ++)
                if(board_queue[i][j].size() == 1) board[i][j] = *(board_queue[i][j].begin()) + '1';
  	}
    void solveSudoku(vector<vector<char> > &board) {
        bool ret = FillBoardQueue(board);
        if(ret == false) return ;
        FillItem();
		while(1){
            if(GuessItem()) break;
        }
        FillBoard(board);
    }
};
void print(vector<vector<char> > &board)
{
	for(int i = 0; i < 9; i ++)
	{
		for(int j = 0 ; j < 9 ; j ++)
		{
			cout << board[i][j] << " " ;
		}
		cout << endl;
	}
}
int main()
{
	Solution s;
	char grid[][9] = {	{'5','3','.',  '.','7','.',  '.','.','.'},
						{'6','.','.',  '1','9','5',  '.','.','.'},
						{'.','9','8',  '.','.','.',  '.','6','.'},
								   
						{'8','.','.',  '.','6','.',  '.','.','3'},
						{'4','.','.',  '8','.','3',  '.','.','1'},
						{'7','.','.',  '.','2','.',  '.','.','6'},
								   
						{'.','6','.',  '.','.','.',  '2','8','.'},
						{'.','.','.',  '4','1','9',  '.','.','5'},
						{'.','.','.',  '.','8','.',  '.','7','9'},
					};
	string grid2[9] = {"...2...63","3....54.1","..1..398.",
					   ".......9.","...538...",".3.......",
					   ".263..5..","5.37....8","47...1..."
					};
	vector<vector<char> > board;
	board.resize(9);
	for(int i = 0; i < 9; i ++)
	{
		board[i].resize(9);
		for(int j = 0 ; j < 9 ; j ++)
		{
			board[i][j] = grid2[i][j];
		}
	}
	s.solveSudoku(board);
	print(board);	
	return 0;
}
