#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

class BigInt {
private:
	static const int MAXN = 100;
	int a[MAXN], len;	// a��ÿһλ������, lenΪ�������ĳ���
	bool negative;		// �Ƿ��Ǹ���
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
/ ���캯��, intת������
/ para x: ��Ҫת�ɴ�������int��
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
/ ���캯��, stringת������
/ para s: ��Ҫת�ɴ��������ַ���
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
/ ���� =, ͬ����ֱ�Ӹ�ֵ
********************************/
BigInt BigInt::operator = (const BigInt &y) {
	len = y.len;
	negative = y.negative;
	memcpy(a, y.a, sizeof(a));
	return *this;
}

/********************************
/ ���� =, ͨ�����캯��ʵ��intתBigInt
********************************/
BigInt BigInt::operator = (const int &y) {
	return *this = BigInt(y);
}

/********************************
/ ���� =, ͨ�����캯��ʵ��stringתBigInt
********************************/
BigInt BigInt::operator = (const char s[]) {
	return *this = BigInt(s);
}

/********************************
/ ���� <
/ return: �Ƿ�С�� y
********************************/
bool BigInt::operator < (const BigInt &y) const {
	if (negative == y.negative)
		return negative ^ abs_lower(*this, y);
	else
		return negative;
}

/********************************
/ ���� ==
/ return: �Ƿ���� y
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
/ ���� !=
/ return: �Ƿ񲻵��� y
********************************/
bool BigInt::operator != (const BigInt &y) const {
	return !(*this == y);
}

/********************************
/ ���� >=
/ return: �Ƿ�С�� y
********************************/
bool BigInt::operator >= (const BigInt &y) const {
	return !(*this < y);
}

/********************************
/ ���� >
/ return: �Ƿ���� y
********************************/
bool BigInt::operator > (const BigInt &y) const {
	return *this >= y && *this != y;
}

/********************************
/ ���� <=
/ return: �Ƿ񲻴��� y
********************************/
bool BigInt::operator <= (const BigInt &y) const {
	return !(*this > y);
}

/********************************
/ ���� +=
/ return: ����y���ֵ
********************************/
BigInt BigInt::operator += (const BigInt &y) {
	return *this = (*this + y);
}

/********************************
/ ���� -=
/ return: ��ȥy���ֵ
********************************/
BigInt BigInt::operator -= (const BigInt &y) {
	return *this = (*this - y);
}

/********************************
/ ����ǰ�� ++
/ return: +1 ���ֵ
********************************/
BigInt BigInt::operator ++ () {
	return *this = (*this + BigInt(1));
}

/********************************
/ ����ǰ�� --
/ return: -1 ���ֵ
********************************/
BigInt BigInt::operator -- () {
	return *this = (*this - BigInt(1));
}

/********************************
/ ���غ��� ++
/ return: ԭֵ
********************************/
BigInt BigInt::operator ++ (int) {
	BigInt tmp = *this;
	++(*this);
	return tmp;
}

/********************************
/ ���غ��� --
/ return: ԭֵ
********************************/
BigInt BigInt::operator -- (int) {
	BigInt tmp = *this;
	--(*this);
	return tmp;
}

/********************************
/ ���� +
/ return: ����y֮���ֵ
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
/ ���� -
/ return: ��������ȥy֮���ֵ
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
/ ����ǰ�ø���, ȡ�෴��
/ return: �෴��
********************************/
BigInt BigInt::operator - () const {
	BigInt ans = *this;
	ans.negative ^= 1;
	ans.adjust();
	return ans;
}

/********************************
/ ���������
********************************/
void BigInt::print() {
	if (negative)
		printf("-");
	for (int i = len; i; i--)
		printf("%d", a[i]);
}

/********************************
/ �ж������������ľ���ֵ��С
/ para x, y: ����������
/ return: |x| �Ƿ�С�� |y|
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
/ ���������ľ���ֵ���
/ para x, y: ��������
/ return: ������|x| + |y|, ����Ϊ��
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
/ ���������ľ���ֵ���
/ para x, y: ��������
/ return: ������|x| - |y|, �з���
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
/ ����len��ֵ, ���ڼӼ���������
********************************/
void BigInt::adjust() {
	while(len > 1 && !a[len])
		len--;
	if (len == 1 && !a[1])
		negative = 0;
}
