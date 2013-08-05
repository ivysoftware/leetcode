#include <vector>
#include <iostream>
using namespace std;
int main(){
	vector<int> v;
	v.push_back(1);
	cout<<v.size()<<endl;
	cout<<v[0]<<endl;
	string s="hello world";
	string temp = s.substr(0, 1);
	vector<string> curParts;
	curParts.push_back(temp);
	cout<<curParts[0]<<endl;
}
