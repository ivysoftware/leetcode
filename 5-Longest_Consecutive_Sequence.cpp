/*5 Longest Consecutive Sequence*/
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(num.size()==0)
        	return 0;
        //1. find min and max
		int min=num[0];
        int max=num[0];
        for(int i=1; i< num.size(); i++){
        	if(min > num[i]){
        		min = num[i];
        		continue;
        	}
			if(max < num[i])
				max = num[i];
        }
        //2. create fill number
        int* range = new int[max-min+1];
        for(int i=0; i< max-min+1; i++){
			range[i] = 0;
		}
		for(int i=0; i< num.size(); i++){
			range[num[i]-min] = 1;
		} 
		bool isCons = false;
		int maxLen = 0;
		int length = 0;
        for(int i=0; i< max-min+1; i++){
			if(range[i] == 0 && !isCons)
				continue;
			if(range[i] == 1){
				length ++;
				isCons = true;
			}				
			else {
				if(maxLen < length)
					maxLen = length;
				length = 0;
				isCons = false;
			}
		}  
		delete []range;
		return maxLen;      
	}
};
int main(){
	Solution s;
	vector<int> nums;
	int values[]={2147483646,-2147483647,0,2,2147483644,-2147483645,2147483645};
	for(int i = 0; i< 7; i++)
		nums.push_back(values[i]);
	int r = s.longestConsecutive(nums);
	cout<<r<<endl;
} 
