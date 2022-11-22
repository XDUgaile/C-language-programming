#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

class BigInt {
private:
	static const int MAXN = 100;
	int a[MAXN], len;	// a中每一位存数字, len为大整数的长度
	bool negative;		// 是否是负数
	bool abs_lower(const BigInt &x, const BigInt &y) const;
	BigInt abs_plus(const BigInt &x, const BigInt &y) const;
	BigInt abs_minus(const BigInt &x, const BigInt &y) const;
	void adjust();
public:
	BigInt(const int x = 0);
	BigInt(const char s[]);
	bool operator < (const BigInt &y) const;
	bool operator == (const BigInt &y) const;
	bool operator != (const BigInt &y) const;
	bool operator >= (const BigInt &y) const;
	bool operator > (const BigInt &y) const;
	bool operator <= (const BigInt &y) const;
	BigInt operator += (const BigInt &y);
	BigInt operator -= (const BigInt &y);
	BigInt operator ++ ();
	BigInt operator -- ();
	BigInt operator ++ (int);
	BigInt operator -- (int);
	BigInt operator + (const BigInt &y) const;
	BigInt operator - (const BigInt &y) const;
	BigInt operator = (const BigInt &y);
	BigInt operator = (const int &y);
	BigInt operator = (const char s[]);
	BigInt operator - () const;
	void print();
};

/********************************
/ 构造函数, int转大整数
/ para x: 需要转成大整数的int型
********************************/
BigInt::BigInt(const int x) {
	memset(a, 0, sizeof(a));
	len = 0;
	negative = x < 0;
	int tmp = abs(x);
	do {
		a[++len] = tmp % 10;
		tmp /= 10;
	} while(tmp);
}

/********************************
/ 构造函数, string转大整数
/ para s: 需要转成大整数的字符串
********************************/
BigInt::BigInt(const char s[]) {
	memset(a, 0, sizeof(a));
	negative = s[0] == '-';
	len = strlen(s) - negative;
	for (int i = 0; i < len; i++)
		a[len - i] = s[i + negative] - '0';
	adjust();
}

/********************************
/ 重载 =, 同类型直接赋值
********************************/
BigInt BigInt::operator = (const BigInt &y) {
	len = y.len;
	negative = y.negative;
	memcpy(a, y.a, sizeof(a));
	return *this;
}

/********************************
/ 重载 =, 通过构造函数实现int转BigInt
********************************/
BigInt BigInt::operator = (const int &y) {
	return *this = BigInt(y);
}

/********************************
/ 重载 =, 通过构造函数实现string转BigInt
********************************/
BigInt BigInt::operator = (const char s[]) {
	return *this = BigInt(s);
}

/********************************
/ 重载 <
/ return: 是否小于 y
********************************/
bool BigInt::operator < (const BigInt &y) const {
	if (negative == y.negative)
		return negative ^ abs_lower(*this, y);
	else
		return negative;
}

/********************************
/ 重载 ==
/ return: 是否等于 y
********************************/
bool BigInt::operator == (const BigInt &y) const {
	if (len == y.len) {
		for (int i = 1; i <= len; i++)
			if (a[i] != y.a[i])
				return false;
		return true;
	}
	return false;
}

/********************************
/ 重载 !=
/ return: 是否不等于 y
********************************/
bool BigInt::operator != (const BigInt &y) const {
	return !(*this == y);
}

/********************************
/ 重载 >=
/ return: 是否不小于 y
********************************/
bool BigInt::operator >= (const BigInt &y) const {
	return !(*this < y);
}

/********************************
/ 重载 >
/ return: 是否大于 y
********************************/
bool BigInt::operator > (const BigInt &y) const {
	return *this >= y && *this != y;
}

/********************************
/ 重载 <=
/ return: 是否不大于 y
********************************/
bool BigInt::operator <= (const BigInt &y) const {
	return !(*this > y);
}

/********************************
/ 重载 +=
/ return: 加上y后的值
********************************/
BigInt BigInt::operator += (const BigInt &y) {
	return *this = (*this + y);
}

/********************************
/ 重载 -=
/ return: 减去y后的值
********************************/
BigInt BigInt::operator -= (const BigInt &y) {
	return *this = (*this - y);
}

/********************************
/ 重载前置 ++
/ return: +1 后的值
********************************/
BigInt BigInt::operator ++ () {
	return *this = (*this + BigInt(1));
}

/********************************
/ 重载前置 --
/ return: -1 后的值
********************************/
BigInt BigInt::operator -- () {
	return *this = (*this - BigInt(1));
}

/********************************
/ 重载后置 ++
/ return: 原值
********************************/
BigInt BigInt::operator ++ (int) {
	BigInt tmp = *this;
	++(*this);
	return tmp;
}

/********************************
/ 重载后置 --
/ return: 原值
********************************/
BigInt BigInt::operator -- (int) {
	BigInt tmp = *this;
	--(*this);
	return tmp;
}

/********************************
/ 重载 +
/ return: 加上y之后的值
********************************/
BigInt BigInt::operator + (const BigInt &y) const {
	if (negative == y.negative) {
		BigInt ans = abs_plus(*this, y);
		ans.negative = negative;
		return ans;
	}
	else
		return negative ? abs_minus(y, *this) : abs_minus(*this, y);
}

/********************************
/ 重载 -
/ return: 大整数减去y之后的值
********************************/
BigInt BigInt::operator - (const BigInt &y) const {
	if (negative == y.negative) {
		BigInt ans = abs_minus(*this, y);
		ans.negative ^= negative;
		return ans;
	}
	else {
		BigInt ans = abs_plus(*this, y);
		ans.negative = negative;
		return ans;
	}
}

/********************************
/ 重载前置负号, 取相反数
/ return: 相反数
********************************/
BigInt BigInt::operator - () const {
	BigInt ans = *this;
	ans.negative ^= 1;
	ans.adjust();
	return ans;
}

/********************************
/ 输出大整数
********************************/
void BigInt::print() {
	if (negative)
		printf("-");
	for (int i = len; i; i--)
		printf("%d", a[i]);
}

/********************************
/ 判断两个大整数的绝对值大小
/ para x, y: 两个大整数
/ return: |x| 是否小于 |y|
********************************/
bool BigInt::abs_lower(const BigInt &x, const BigInt &y) const {
	if(x.len == y.len) {
		for(int i = x.len; i >= 1; i--)
			if(x.a[i] < y.a[i])
				return true;
			else if (x.a[i] > y.a[i])
				return false;
		return false;
	}
	return x.len < y.len;
}

/********************************
/ 两大整数的绝对值相加
/ para x, y: 两大整数
/ return: 大整数|x| + |y|, 符号为正
********************************/
BigInt BigInt::abs_plus(const BigInt &x, const BigInt &y) const {
	BigInt ans;
	ans.len = max(x.len, y.len) + 1;
	for(int i = 1; i <= ans.len; i++) {
		ans.a[i] += x.a[i] + y.a[i];
		ans.a[i+1] = ans.a[i] / 10;
		ans.a[i] %= 10;
	}
	ans.adjust();
	return ans;
}

/********************************
/ 两大整数的绝对值相减
/ para x, y: 两大整数
/ return: 大整数|x| - |y|, 有符号
********************************/
BigInt BigInt::abs_minus(const BigInt &x, const BigInt &y) const {
	if(abs_lower(x, y)) {
		BigInt ans = abs_minus(y, *this);
		ans.negative = 1;
		return ans;
	}
	BigInt ans;
	ans.len = max(x.len, y.len);
	for(int i = 1; i <= ans.len; i++) {
		if(x.a[i] < y.a[i]) {
			ans.a[i + 1]--;
			ans.a[i] += 10;
		}
		ans.a[i] += x.a[i] - y.a[i];
	}
	ans.adjust();
	return ans;
}

/********************************
/ 调整len的值, 用于加减法运算中
********************************/
void BigInt::adjust() {
	while(len > 1 && !a[len])
		len--;
	if (len == 1 && !a[1])
		negative = 0;
}
