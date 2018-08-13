//
// Created by Administrator on 2018/8/13.
//

//#include "share.h"

#include <vector>
#include <iostream>
#include<queue>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

void adjust_core(vector<int>& nums, int p) {
    if (p < (nums.size() + 1) / 2) {
        int lchild = p * 2 + 1;
        int rchild = p * 2 + 2;
        int maxone = p;
        int tmp;
        if (lchild < nums.size() && nums[maxone] < nums[lchild])
            maxone = lchild;
        if (rchild < nums.size() && nums[maxone] < nums[rchild])
            maxone = rchild;
        if (p != maxone) {
            tmp = nums[p];
            nums[p] = nums[maxone];
            nums[maxone] = tmp;
        }
    }
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    if (nums.empty())
        return NULL;
    for (int i = (nums.size() - 1)/2; i >= 0; i--) {
        adjust_core(nums, i);
    }
    queue<TreeNode*> q;
    TreeNode *root = new TreeNode(nums[0]);
    q.push(root);
    int level_num = 1;
    for (int i = 0; i<(nums.size()+1)/2; i++) {
        TreeNode *p = q.front();
        q.pop();
        if (i * 2 + 1 < nums.size()) {
            TreeNode *lchild = new TreeNode(nums[i * 2 + 1]);
            p->left = lchild;
            q.push(lchild);
        }
        if (i * 2 + 2 < nums.size()) {
            TreeNode *rchild = new TreeNode(nums[i * 2 + 2]);
            p->right = rchild;
            q.push(rchild);
        }

    }
    return root;
}
int test() {

    //fans_group();
    //merge_overlap();
    int arr[] = { 3,2,1,6,0,5 };
    vector<int> nums(arr, arr + 6);
    constructMaximumBinaryTree(nums);
    return 0;
}
