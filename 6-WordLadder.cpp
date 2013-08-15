/*6-Word Ladder*/
#include <iostream>
#include <vector>
#include <string>
#include <tr1/unordered_set>
#include <queue>
using namespace std;
using std::tr1::unordered_set;

//DFS遍历，复杂度高，不知道为什么有run time error(表明编代码能力的素质尚待提高)
//此段代码是写代码后，编译一次通过，0错误的第一次
//虽然还有run time error, 不能一气呵成让人知道得谦虚啊 
class Solution1 {
public:
	vector<vector<int> > minPathList;
	vector<vector<int> > diffTable;
	int sLen;
	int calDiff(string& s1, string& s2){
		if(s1.length() == 0)
			return s2.length();
		if(s2.length() == 0)
			return s1.length();
		int diff = 0;
		for(int i=0;i<s1.length(); i++){
			if(s1[i] != s2[i])
				diff += 1;
		} 
		return diff;
	}
	void fillDiffTable(vector<string>& slist){
		if(slist.size() == 0)
			return;
		for(int i = 0; i < slist.size(); i++){
			vector<int> diffList;
			for(int j = 0; j < slist.size(); j++){
				int diffNum = 0;				
				if(i!=j)
					diffNum = calDiff(slist[i], slist[j]);
				//else if(i > j)
				//	diffList.push_back(diffList[j][i]);//don't know whether it is right
				diffList.push_back(diffNum);
				//cout<<slist[i]<<":"<<slist[j]<<"="<<diffNum<<endl;
			}
			diffTable.push_back(diffList);
		}	
	}
	//数组传递，怎么深度复制构造呢？ 
	int calPathRecur(int start, int end, vector<int> &remains, int globalMin, int preLen, vector<int>& prePath){
		if(start == end && globalMin == preLen){//表明回溯过程 
			minPathList.push_back(vector<int>(prePath.begin(), prePath.end()));
		} 
		if(start == end) 
			return 0;
		int minLen = sLen+1;
		for(int i= 0; i<remains.size(); i++ ){
			if(remains[i] == 1) //表示此元素已经被访问过 
				continue;
			int curStep = i;
			if(diffTable[start][curStep] != 1)
				continue;
			remains[i] = 1;
			if(globalMin < sLen+1){
				prePath.push_back(curStep); 
			} 
			int curLen = calPathRecur(curStep, end, remains, globalMin, preLen+1, prePath );
			if (minLen > curLen)
				minLen = curLen;
			remains[i] = 0;//reset 
			if(globalMin < sLen+1){
				prePath.pop_back(); 
			} 
		}
		//cout<<allw[start]<<" "<<minLen+1<<endl;
		return minLen+1;//经过几个节点到达目的节点 
	}
	
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for(int i=0;i < diffTable.size(); i++)
            vector<int>().swap(diffTable[i]);
        for(int i=0; i< minPathList.size(); i++ )
            vector<int>().swap(minPathList[i]);
        vector<vector<string> > result;
        vector<string> allWords(dict.begin(), dict.end());
        allWords.push_back(end);
        allWords.push_back(start);
        sLen = allWords.size();
        //1.        
        fillDiffTable(allWords);
		//2. 
       	vector<int> sList(sLen);//表示该点是否被访问过 
		for(int i=0; i<sLen; i++){
			sList[i] = 0;
		} 
		sList[sLen-1] = 1;
		vector<int> prePath;
        int minLen = calPathRecur(sLen-1, sLen-2,sList, sLen+1,0, prePath);
        if(minLen > sLen) //如果没找到路径 
        	return result;
        //cout<<"min length ="<<minLen<<endl;
		//3. get path; remember param reset
        prePath.push_back(sLen - 1);
		for(int i=0; i<sLen; i++){
			sList[i] = 0;
		} 
		sList[sLen-1] = 1;
        calPathRecur(sLen-1, sLen-2,sList, minLen,0, prePath);//0代表从当前节点出发，还没经过任何节点
        
		//4. output
        for(int i = 0; i < minPathList.size(); i++){
        	vector<string> eachresult;
        	for(int j = 0; j < minPathList[i].size(); j++){
        		eachresult.push_back(allWords[minPathList[i][j]]);
        	}
        	result.push_back(eachresult);
        }
        
        return result;
    }
};

class Solution{
public:
	vector<vector<int> > adj;
	vector<vector<int> > prev;
	vector<string> sList;
	int startPos;
	int endPos;
	vector<vector<string> > result;
	int calDiff(const string& s1, const string& s2){
		if(s1.length() == 0)
			return s2.length();
		if(s2.length() == 0)
			return s1.length();
		int diff = 0;
		for(int i=0;i<s1.length(); i++){
			if(s1[i] != s2[i])
				diff += 1;
		} 
		return diff;
	}
	void FillAdj(){
		for(int i=0; i< sList.size(); i++){
			prev.push_back(vector<int>());
			for(int j=0; j< sList.size(); j++){
				if(i == j) continue;
				int diffNum = calDiff(sList[i], sList[j]);
				if(diffNum == 1){
					prev.back().push_back(j); 
				}
			}
		}
	}
	int GetShortestLen(){
		queue<int> q(1, startPos);
		//BFS
		while(!q.empty()){
			for(int i = 0; i< q.size(); i ++){
				
			}
		}
	}
	vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		//
		if(start == end){
			result.push_back(vector<string>(1,start));
			return result;
		}
		dict.insert(start);
		dict.insert(end);
		sList.clear();
		for(unordered_set<string>::iterator it=dict.begin(); it != dict.end(); it++){
			if(*it == start)
				startPos = sList.size();
			if(*it == end)
				endPos = sList.size();
			sList.push_back(*it);
		}
		//1. fill adjecent matrix to indicate next node choices
		FillAdj();
		//2. BFS find the shortest path
		GetShortestLen();
		//3.
	}
}; 
int main(){
	Solution s;
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("c");
	//dict.push_back("log");
	vector<vector<string> >  result = s.findLadders("hit", "cog", dict);
	for(int i=0; i< result.size(); i++){
		for(int j = 0; j< result[i].size(); j++){
			cout<<result[i][j]<<" ";
		}
		cout<<endl;
	}
}
