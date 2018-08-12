//
// Created by Administrator on 2018/8/12.
//

#ifndef BYTEDANCE_SHARE_H
#define BYTEDANCE_SHARE_H
using namespace std;

#include <iostream>
#include <vector>
#include <string>
typedef pair<int,int> PAIR;
ostream& operator << (ostream& out, const PAIR& src);
bool less_pair ( PAIR& src,  PAIR& dst);

void mprint(const vector<vector<int>>& matrix);
void str2matrix(string str_arr[], vector<vector<int>>& matrix);

void fans_group();
void merge_overlap();

#endif //BYTEDANCE_SHARE_H
