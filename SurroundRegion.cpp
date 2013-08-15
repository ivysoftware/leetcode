/*SurroundedRegion*/
 
#include<vector>
#include<iostream>
#include <Exception>
using namespace std;
class Solution {
public:
	struct Point{
		int row;
		int col;
		Point(int i, int j):row(i),col(j){}
	};
	int Length;
	int Width;
	void BFSMark(vector<vector<char> > &board, int i, int j){
		vector<Point> queuelist;
		queuelist.push_back(Point(i,j));
		static int direction[4][2]={{0,1}, {0,-1}, {1,0}, {-1,0}};
		while(queuelist.size() > 0){
			Point p = queuelist.back();	
			queuelist.pop_back();						
			for(int index=0; index<4; index++){
				int row = p.row + direction[index][0];
				int col = p.col + direction[index][1];
				if((row >=0 && row < Width) && (col >= 0 && col< Length) && board[row][col] == 'O'){
					board[row][col] = '+';
					queuelist.push_back(Point(row, col));
				}
			}
		}


	}
	void MarkBorder(vector<vector<char> > &board){
		for(int i = 0; i < Length; i++) {
			if(board[0][i] == 'O') {
				board[0][i] = '+'; 
				BFSMark(board, 0, i ); 
			} 
			if(board[Width-1][i] == 'O') {
				board[Width-1][i] = '+';
				BFSMark(board, Width-1, i);
			}
		}
    	for(int j = 0; j < Width; j++) {
    		if (board[j][0] == 'O') {
    			board[j][0] = '+';
    			BFSMark(board, j, 0);
    		} 
			if(board[j][Length-1] == 'O') {
				board[j][Length-1] = '+';
				BFSMark(board, j, Length - 1);
			}
		}

	}	
    void solve(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		Width = 0;
		Length = 0;        
        Width = board.size();
        if(board.size() > 0){ //访问有效性 
        	Length = board[0].size();
        }
        //特殊情况，一行，两行，一列，两列都不考虑 
        if(Length <= 2 || Width <= 2)
        	return;
        //mark the four border to "+"
        MarkBorder(board);
		//from (1,1) to (width-2, length-2 ) matrix 
		for(int i = 0; i < Width; i++)
		{
			for(int j = 0; j < Length; j++)
			{
				if(board[i][j] == 'X')
					continue;
				if(board[i][j] == 'O')
				{
					board[i][j] = 'X';
				}else if(board[i][j] == '+'){
					board[i][j] = 'O';
				}
			}
		} 
    }
};

int main(){
	Solution s;
	vector<vector<char> > board;
	int length = 2;
	int width = 3;
	//给定字符串数组，怎么将它放入二维数组呢？？？ 
	//cin>>width>>length;
	//2. init board
	for(int i = 0; i < width; i++){
		vector<char> line;
		for(int j = 0; j < length; j++){
			char value = i*length+j + '0' + 1;
			line.push_back(value);
			cout<<i<<":"<<j<<value<<endl; 
		}
		//cout<<line[0]<<endl;
		board.push_back(line);
	}
	cout<<board.size()<<" ";
	if(board.size()> 0)
		cout<<board[0].size()<<endl;
	cout<<board[0][0]<<" " <<board[1][0]<<" "<<board[2][1]<<endl;
		/*
	//3. solve
	s.solve(board);
	//4. output
	for(int i = 0; i < width; i++){
		for(int j = 0; j < length; j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}*/	
}
