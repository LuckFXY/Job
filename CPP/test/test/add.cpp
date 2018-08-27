//#include <iostream>
//#include <vector>
//#include <set>
//#include <map>
//using namespace std;
//
//class BigNum {
//	bool positive;
//	string data;
//public:
//	BigNum() {
//		positive = true;
//	}
//	BigNum(string s) {
//		positive = true;
//		data = s;
//	}
//	string get() {
//		string out;
//		const int n = data.size();
//		out.resize(n);
//		for (int i = 0; i < n; i++) {
//			out[n - 1 - i] = data[i];
//		}
//		return out;
//	}
//	BigNum& operator=(const BigNum& num);
//	BigNum& operator=(const string& s);
//	BigNum& operator>(const string& s);
//	BigNum& operator<(const string& s);
//	BigNum& operator==(const string& s);
//	void add(const BigNum& b);
//	void sub(const BigNum& c);
//};
//BigNum& BigNum::operator=(const BigNum& num) {
//	if (this != &num) {
//		delete &data;
//	}
//	data = num.data;
//	return *this;
//}
//BigNum& BigNum::operator=(const string &s) {
//	int n = s.size();
//	data.resize(n);
//	for (int i = 0; i < s.size(); i++) {
//		data[n - 1 - i] = s[i];
//	}
//	return *this;
//}
//BigNum& BigNum::operator>(const string& s) {
//	return data > s.data;
//}
//BigNum& BigNum::operator<(const string& s) {
//	return data < s.data;
//}
//BigNum& BigNum::operator==(const string& s) {
//	return data == s.data;
//}
//void BigNum::add(const BigNum& b) {
//	int i = 0, j = 0;
//	int c, carry = 0;
//	while (i < data.size() && j < b.data.size()) {
//		c = data[i] + b.data[j] + carry - 96;
//		carry = 0;
//		if (c > 9) {
//			carry = 1;
//			c -= 10;
//		}
//		data[i] = c + 48;
//		i += 1;
//		j += 1;
//	}
//	while (i < data.size()) {
//		c = data[i] + carry - 48;
//		carry = 0;
//		if (c > 9) {
//			carry = 1;
//			c -= 10;
//		}
//		data[i] = c + 48;
//		i += 1;
//	}
//	while (j < data.size()) {
//		c = b.data[j] + carry - 48;
//		carry = 0;
//		if (c > 9) {
//			carry = 1;
//			c -= 10;
//		}
//		data += (char)(c + 48);
//		i += 1;
//	}
//	if (carry) {
//		data += (char)(c + 48);
//	}
//}
//void BigNum::sub(const BigNum& b) {
//
//	if (b.data > data) {
//		positive = false;
//		const string& big = b.data;
//		string& small = data;
//	}
//	else {
//		string& big = data;
//		const string& small = b.data;
//	}
//}
////int main() {
////
////	BigNum a, b;
////	a = "123456789";
////	b = "987654321";
////	a.add(b);
////	string out;
////	out = a.get();
////	cout << out.c_str() << endl;
////	return 0;
////}