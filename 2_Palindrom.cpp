/*Minimum cut of palindrom*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
	bool** IsPalindrom;
    bool CheckPalindrom(string &src, unsigned int row, unsigned int col){
      int start = row;
      int end = col;
      while(src[start] == src[end] && start < end ){
        start ++;
        end --;
      }
      if(start >= end)
        return true;
      else 
        return false;
    }
    
    
    void FillInStatus(string &src, unsigned int length){
        if(src == "" || length == 0) 
    		return ;
    	//c++ 不初始化也不提醒 
    	if(IsPalindrom == NULL){
    		IsPalindrom = new bool*[length];
    		for(int i = 0; i< length; i++){
    			IsPalindrom[i] = new bool[length];
    		}
    	}
    	//单独一个字符为回文	
    	for(int i = 0; i < length; i++)
    		IsPalindrom[i][i] = true;
    	//判断从i开始的所有字符串是否为回文
    	for(int i = 0; i < length; i++){
    		for(int t = 1; (t+i) < length; t++ ){
    			IsPalindrom[i][i+t] = CheckPalindrom(src, i, i+t);
    			//cout<<i<<"-"<<t+i<<":" <<IsPalindrom[i][i+t]<<" ";
    		} 
    		//cout<<endl;
    	} 
    }
    bool GenPalindromParts(int start, int curLen, string& s, unsigned int sLen, 
    						vector<string>& former, vector< vector<string> > &results){
    	if(curLen == 0){
    		results.push_back(former);
    		return false;
    	}
    	//cout<<"start : " << start<< " curLen" <<curLen <<endl;
    	//遍历每一个从当前字符开始的回文情况，右侧起始是指字符在字符串中的位置
        for(int i = 0; i < curLen; i++ ){
        	if(IsPalindrom[start][start+i]){ 
        		vector<string> newbranch(former.begin(), former.end());
        		string temp = s.substr(start, i+1);
    			//cout<<"new branch: "<<temp<<endl;
        		newbranch.push_back(temp);
        		//GenPalindromParts(i+1, curLen-i-1, s, sLen, newbranch, results);
        		GenPalindromParts(start+i+1, curLen-i-1, s, sLen, newbranch, results);  //
        	}
        }
        return true;
    }
    vector< vector<string> > partition(string &s) {
    	// Start typing your C/C++ solution below
    	// DO NOT write int main() 
    	//cout<<"original " <<s <<endl;
    	IsPalindrom = NULL; //最后的大bug解决，是类中的变量要初始化，否则为随机值 
        vector< vector<string> > results;
        if(s.length() == 0) // || s == NULL
    		return results;
        if(s.length() == 1 ){
        	vector<string> curParts;
        	curParts.push_back(s);
        	results.push_back(curParts);
        	return results;
        }
        unsigned int sLen = s.length();
        FillInStatus(s, sLen);
    	// 易混淆，start, len 和 start, end
    	std::vector<string> tmp; // vector 传参！！ 能在句子里面写吗？ 
    	GenPalindromParts(0, sLen, s, sLen,tmp, results);
        for(int i =0 ;i<sLen ; i++)
            delete[] IsPalindrom[i];
    	return results;
    }

};
int main(){
	Solution s; 
	string a;
	cin>>a;
	vector<vector<string> > parts = s.partition(a);
	int row = parts.size();
	//cout<<"result size is " << row<<endl; 
	for(int i=0; i< row; i++){
		int col = parts[i].size();
		for(int j = 0; j < col; j++){
			cout<<parts[i][j]<<" ";
		}
		cout<<endl;
	}
	
}
