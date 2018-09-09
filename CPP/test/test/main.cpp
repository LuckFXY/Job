//
// Created by Administrator on 2018/9/8.
//

#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>


using namespace std;
inline bool isNum(char ch) {
	if (ch == '.' || ('0' <= ch && ch <= '9'))
		return true;
	else
		return false;
}
inline long str2myfloat(const string &s, int start, int end){
	long ret=0;
	int i=start;
	for (i = start; i < end && s[i] != '.'; i++) 
		ret = ret * 10 + s[i] - 48;
	
	if (i < end && s[i] == '.') i += 1;
	for (;i < end;i++)
		ret = ret * 10 + s[i] - 48;
	return ret;
}
void split_string(string s, vector<long> &ret) {
	unsigned j = 0;
	vector<long> ret;
	for (unsigned i = 0; i<s.size();) {
		if (!isNum(s[i])) {
			i += 1;
		}
		else {
			j = i;
			while (isNum(s[j]))
				j += 1;
			long tmp = str2myfloat(s,i,j);
			ret.push_back(tmp);
			i = j;
			}
		}
}

int main() {
	float total, num, min, max;
	string s = "总金额10.56元，一共5个人，最小金额1.8，最大金额3";
	vector<long> ret;
	split_string(s, ret);
	if (4 != ret.size()) return -1;
	long total = ret[0];
	long num = ret[1];
	long min = ret[2];
	long max = ret[3];
	long cur = 100;
	if
}