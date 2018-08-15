//#include "share.h"

#include <vector>
#include <iostream>
#include<queue>
using namespace std;

struct TreeNode {

	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x) {
		val = x;
		left = nullptr;
		right = nullptr;
	}
};

void struct_core(vector<int>& nums, int left, int right, TreeNode *&root) {

	if (left > right)
		root =  NULL;
	else if (left == right) {
		root = new TreeNode(nums[left]);
	}

	else{
		int max = left;
		for (int i = left + 1; i<= right; i++) {
			if (nums[i] > nums[max])
				max = i;
		}
		root = new TreeNode(nums[max]);
		struct_core(nums, left, max - 1, root->left);
		struct_core(nums, max + 1, right, root->right);
	}
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	TreeNode * root;
	struct_core(nums, 0, nums.size() - 1, root);
	return root;
}
int main() {

	//fans_group();
	//merge_overlap();
	int arr[] = { 3,2,1,6,0,5 };
	vector<int> nums(arr, arr + 6);
	constructMaximumBinaryTree(nums);
	return 0;
}
