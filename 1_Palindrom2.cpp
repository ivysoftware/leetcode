/*Minimum cut of palindrom*/
#include <iostream>
#include <vector>
using namespace std;
bool CheckPalindrom(char* src, unsigned int length){
  char* start = src;
  char* end = src + length-1;
  while(*start == *end && start < end ){
    start ++;
    end --;
  }
  if(start >= end)
    return true;
  else 
    return false;
}
int MinimumCutOfPalindromReCur(char* start , unsigned int length){
  if(length == 1)
    return 1;
  bool isPalindrom =  CheckPalindrom(start, length);
  if(isPalindrom == true)
    return 1;
  int minCut = 100000;
  for(int i = 0; i< length-1; i++){
    int curPartitionCut = MinimumCutOfPalindromReCur(start, i+1) + MinimumCutOfPalindromReCur(start+i+1, length-i-1);
    if(minCut > curPartitionCut)
      minCut = curPartitionCut;
  }
  return minCut;
}
int MinimumCutOfPalindrom(char* src, unsigned int length){
  if(src == NULL)
      return 0;

    int minCut = 100000;
    for(int i = 0; i< length-1; i++){    	
      int curPartitionCut = MinimumCutOfPalindromReCur(src, i+1) + MinimumCutOfPalindromReCur(src+i+1, length-i-1);
      //cout<<i<<":"<<curPartitionCut<<" ";
      if(minCut > curPartitionCut)
        minCut = curPartitionCut;
    }
    //cout<<endl;
    return minCut-1;
} 
bool** IsPalindrom;
int* results;
void FillInStatus(char* src, unsigned int length){
	if(IsPalindrom == NULL || src == NULL || length == 0)
		return ;
	for(int i = 0; i < length; i++)
		IsPalindrom[i][i] = true;
	for(int i = 0; i < length; i++){
		for(int t = 1; (t+i) < length; t++ ){
			IsPalindrom[i][i+t] = CheckPalindrom(src+i, t+1 );
			//cout<<i<<"-"<<t+i<<":" <<IsPalindrom[i][i+t]<<" ";
		} 
		//cout<<endl;
	} 
}
int GetMinCut(unsigned int pos, unsigned int length){
	if(pos == 0)
		return 0;
	if(IsPalindrom[0][pos] == true)
		return 0;
	int min = length;
	for(int i=pos; i >=1; i--){
		if(IsPalindrom[i][pos] == true){
			int curCut = 1 + results[i-1];
			if(min > curCut )
				min = curCut; 
		}
	}
	return min;
}

int MinimumCutOfPalindrom_better(char* src, unsigned int length){
	if(src == NULL || length == 0)
		return 0;
	//二维数组的创建与传参，真真要好好掌握 
	IsPalindrom = new bool*[length];
	for(int i = 0; i< length; i++){
		IsPalindrom[i] = new bool[length];
	}
	results = new int[length];
	FillInStatus( src, length);
	for(int i=0; i < length; i++){
		results[i] = GetMinCut(i, length);
		//cout<<i<<":"<<results[i]<<" ";
	} 
	//cout<<endl;
	return results[length-1];
}

int minCut(string s) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() 
	char src[5000];
    int i;
	for(i=0; s[i]!='\0';i++)
	    src[i] = s[i];
    src[i] = '\0' ; //must be indeed
    if(i == 0 || i == 1)
      return 0;
    if(CheckPalindrom(src,i))
      return 0;
    //利用两个表格表示 
	return MinimumCutOfPalindrom_better(src, i);
} 
int main(){
	string a;
	cin>>a;
	cout<<minCut(a)<<endl; 
}
