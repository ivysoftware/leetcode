/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <iostream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    void sumNumReCur(TreeNode* root, int* curSum, int parent){
        if(root == NULL){
            return;
        }
        int curValue = parent*10 + root->val;
        if(root->left == NULL && root->right == NULL){
            curSum += curValue;
            return;
        }
        if(root->left != NULL)
            sumNumReCur(root->left, curSum, curValue);
        if(root->right != NULL)
            sumNumReCur(root->right, curSum, curValue);
        
    }
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(root == NULL){ return 0;}
        int sum = 0;
        sumNumReCur(root, &sum, 0);
        return sum;
    }
};
int main(){
	Solution s;
	int sum = s.sumNumbers(new TreeNode(9));
	cout<<sum<<endl;
}

