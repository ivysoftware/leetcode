/*Minimum cut of palindrom*/
#include <iostream>
#include <vector>
using namespace std;
int MinimumCutOfPalindrom(char* src){
	if(src == NULL)
		return -1;
	
	unsigned int length = 0;
	while(*(src+length) != '\0')
		length ++;
	int IsCut[length];
	//memset(IsCut, -1, length);  //memset is not set
	for(int i=0; i< length; i++)
		IsCut[i] = -1;
	IsCut[0] = 1; 

	int pos = 1;
	while(pos < length)
		//odd symmetric
		int i;
		for(i=1; i <= pos && (pos+i) < length; i++){
			if(src[pos-i] != src[pos+i])
				break;
			IsCut[pos-i] = 0;
			IsCut[pos+i] = 0;
			
		}
		if(i > 1){
			pos = pos+i;
			IsCut[pos] = 0;
		}
		//even symmetric		
		int left = pos-1;
		int right = pos;
		while(left >= 0 && right < length && src[left] == src[right]){
			IsCut[left] = 0;
			IsCut[right] = 0;
			left --;
			right ++;
		}
		if(left > = 0)
			IsCut[left] = 1;
		if(right < length)
			IsCut[right] = 1;
		pos = (pos == right) ? pos+1 : right+1;		
	}
	int MinCut = 0;
	for(int i = 0; i< length -1; i++){
		if(IsCut == 1)
			MinCut ++;
		if(IsCut == -1)
			cout<<i<<" "
	}
	cout<<endl;
	return Mincut;
} 
int main(){
	char src[1256];
	cin>>src;
	cout<<MinimumCutOfPalindrom(src)<<endl; 
	
}
