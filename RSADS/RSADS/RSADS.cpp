// RSADS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class RSADS {
private:
	int m_n;//公钥，两个大素数的乘积
	int m_e;//公钥，随机选取的整数
	int m_d;//私钥

public:
	/*生成密钥函数*/
	int KeyGen(int p, int q)
	{
		int  f;
		m_n = p*q;
		f = (p - 1)*(q - 1);
		for (;;)
		{
			m_e = rand() % f;
			if (Gcd(m_e, f) == 1) break;
		}
		m_d = ExtendedEuclid(f, m_e);
		return 0;
	}
	/*签名函数*/
	int Sign(int m)
	{
		return square(m, m_d, m_n);
	}
	/*认证函数*/
	int Verify(int c)
	{
		return square(c, m_e,m_n);
	}
	/*扩展的欧几里得除法*/
	int ExtendedEuclid(int a, int b)//扩展的欧几里得算法
	{
		int s1[3], s2[3];
		s1[0] = a;s1[1] = 1;s1[2] = 0;
		s2[0] = b;s2[1] = 0;s2[2] = 1;
		int temp[3];
		int i, q;
		while (s2[0] != 0) {
			q = s1[0] / s2[0];
			for (i = 0;i<3;i++)
			{
				temp[i] = s1[i] - q*s2[i];
				s1[i] = s2[i];
				s2[i] = temp[i];
			}
		}
		return s1[2];
	}
	/*求最大公约数*/
	int Gcd(int a, int b)
	{
		if (a != 0)
		{
			b = b%a;
			Gcd(b, a);
		}
		else
			return b;
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
	RSADS test;
	int p, q, m;
	cout << "请输入两个大素数p，q：" << endl;
	cin >> p >> q;
	cout << "输入要签名的消息：";
	cin >> m;
	test.KeyGen(p, q);
	int ds = test.Sign(m);
	cout << m<<"的签名是:" << ds<< endl;
	if (test.Verify(ds) == m)cout << "认证通过!"<<endl;
	else cout << "认证失败!" << endl;
    return 0;
}

//p:11 q:13 m:24 c=7 

