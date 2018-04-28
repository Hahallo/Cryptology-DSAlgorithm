// Lamport.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class LamportDS{
private:
	vector<int>skey ;//私钥
	vector<int>pkey ;//公钥
	int m_a;
	int m_b;
public:
	/*确定hash函数f(x)= a^x mod b*/
	LamportDS(int a, int b) {
		m_a = a;
		m_b = b;
	}
	/*得到密钥和公钥*/
	void Getkey(int k) {
		srand((unsigned)time(NULL));
		for (int i = 0;i <2*k;i++)
		{
			int temp= rand() % m_b;//随机取2*k个0到m_b间的整数
			skey.push_back(temp);
			pkey.push_back(Hash(temp));
		}
	}
	/*单向函数*/
	int Hash(int y) {
		return square(m_a,y,m_b);
	}
	/*签名函数*/
	vector<int>Sign(string m) {

		int length = m.size();
		vector<int>sign(length);
		for (int i = 0;i < length;i++)
		{
			sign[i] = skey[2 * i + m[i] - '0'];//签名
		}
		return sign;
	}
	/*验证函数*/
	bool Verify(string m,vector<int>sign) {
		int length = m.size();
		for (int i = 0;i < length;i++)
		{
			if (Hash(sign[i]) != pkey[2 * i + m[i] - '0'])//认证
				return false;
		}
		return true;
	}
	/*求m的e次方模n*/
	int square(int m, int e, int n)
	{

		int a[50];
		int c = 1, i = 0;
		while (e > 1) {
			a[i++] = e % 2;
			e = e / 2;
		}
		a[i] = 1;
		for (i;i > -1;i--)
		{
			c = (c*c) % n;
			if (a[i] == 1)
			{
				c = (c*m) % n;
			}
		}
		return c;
	}
};

int main()
{
	LamportDS test(3, 7879);
	test.Getkey(3);//获得一个2*3长度的私钥
	string m = "010";//明文
	cout << "明文为：" << m<<endl;
	vector<int>s=test.Sign(m);//签名
	cout << "签名为：";
	for (int i : s)
	{
		cout << i << ",";
	}
	cout << endl << "认证结果为：";
	if (test.Verify(m, s))cout <<"验证通过!" << endl;
	else cout << "验证失败!" << endl;
    return 0;
}

