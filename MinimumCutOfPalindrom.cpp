
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
    cout<<length<<endl;
	int IsCut[length];
	//memset(IsCut, -1, length);  //memset is not set
	for(int i=0; i< length; i++)
		IsCut[i] = -1;
	IsCut[0] = 1; 

	int pos = 1;
	while(pos < length){
		//odd symmetric
		int i;
		for(i=1; i <= pos && (pos+i) < length; i++){
			if(src[pos-i] != src[pos+i])
				break;
			IsCut[pos-i] = 0;
			IsCut[pos+i] = 0;
			
		}
		if(i > 1 && i <= pos){
            IsCut[pos-i] = 1;
            IsCut[pos] = 0;
            pos = pos + i;
        }else if (i > 1){
            IsCut[pos] = 0;
			pos = pos+i;
		    continue;	
        } 
          

		//even symmetric		
		int left = pos- 1 ;
		int right = pos;
		for(; left >= 0 && right < length && src[left] == src[right]; left--, right++){
			IsCut[left] = 0;
			IsCut[right] = 0;
		}
		if(left >= 0)
			IsCut[left] = 1;
		if(right < length && pos < right)
			IsCut[right - 1] = 1;
        else if(pos == right)
            IsCut[pos] = 1;
		pos = (pos == right) ? pos+1 : right;		
	}
	int MinCut = 0;
	for(int i = 0; i< length -1; i++){
		if(IsCut[i] == 1)
			MinCut ++;
		//if(IsCut[i] == -1)
		cout<<i<<" "<<IsCut[i]<<" ";
	}
	cout<<endl;
	return MinCut;
} 
int main(){
	char src[1256];
	cin>>src;
	cout<<MinimumCutOfPalindrom(src)<<endl; 
	
}
