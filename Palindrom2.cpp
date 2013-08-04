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

    bool isPalindrom =  CheckPalindrom(src, length);
    if(isPalindrom == true)
      return 1;
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
int minCut(string s) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() 
	char src[5000];
    int i;
	for(i=0; s[i]!='\0';i++)
	    src[i] = s[i];
    src[i] = '\0' ; //must be indeed
    if(i == 0 || i == 1)
      return 1;
    if(CheckPalindrom(src,i))
      return 0;
	return MinimumCutOfPalindrom(src, i);
}
int main(){
	string a;
	cin>>a;
	cout<<minCut(a)<<endl; 
}
