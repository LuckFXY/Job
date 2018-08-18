//
// Created by Administrator on 2018/8/14.
//
#include <iostream>
#include <vector>

using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;
inline void swap(vector<int>& arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
inline void vprint(vector<int> arr){
    for(auto it = arr.begin(); it != arr.end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
}
vector<TreeNode*> generateTrees(int n) {
    vector<int> unique_bst;
    for(int i=1; i<=n; i++)
        unique_bst.emplace_back(i);
    for(int i=n+1; i<2*n; i++)
        unique_bst.emplace_back(0);

    vector<vector<int>> result;
    result.emplace_back(unique_bst);
	vector<TreeNode*> ret;
    int idx = n;
    for(int i=n-1; i>0; i--){
        idx -= 1;
        for(int j=idx; j<2*n; j++){
            if(unique_bst[j+1] == 0 && unique_bst[j-1] != 0) {
                swap(unique_bst, j, j + 1);
                vprint(unique_bst);
                result.emplace_back(unique_bst);
            }
        }
    }
	return ret;
}