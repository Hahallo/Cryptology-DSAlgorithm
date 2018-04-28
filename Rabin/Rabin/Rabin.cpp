// Rabin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

class Rabin {
public:
	/*求m的e次方模n*/
	int squra(int m, int e, int n)
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
	/*加密函数*/
	int Encryption(int m, int n1)
	{
		return m*m%n1;
	}
	/*解密函数                                         */
	/*输入：密文c，私钥p，q（p，q均为4k+3的素数，n=pq）*/
	/*输出：明文m                                      */
	void Decryption(int c, int p, int q)
	{
		//利用扩展的欧几里得除法，求整数s，t，使得sp+tq=1
		int a[3], b[3];
		int u, v, m1, m2, s, t;
		int m[4];
		a[0] = p;a[1] = 1;a[2] = 0;
		b[0] = q;b[1] = 0;b[2] = 1;
		int temp[3];
		int i, j;
		while (b[0] != 0)
		{
			j = a[0] / b[0];
			for (i = 0;i < 3;i++)
			{
				temp[i] = a[i] - j*b[i];
				a[i] = b[i];
				b[i] = temp[i];
			}
		}
		s = a[1];t = a[2];
		u = squra(c, (p + 1) / 4, p);
		v = squra(c, (q + 1) / 4, q);
		m1 = (u*t*q + v*s*p) % (p*q);
		m2 = (u*t*q - v*s*p) % (p*q);
		m[0] = m1;m[1] = (p*q) - m1;
		m[2] = m2;m[3] = (p*q) - m2;
		cout << "调用解密函数，明文为其中之一：" << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << endl;
	}
};
int main()
{
	//测试
	Rabin test;
	int m,c,p,q;
	cout << "输入明文：" << endl;
	cin >> m;
	cout << "请输入私钥：" << endl;
	cin >> p;
	cin >> q;
	c=test.Encryption(m, p*q);
	cout << "密文为:" << c << endl;
	test.Decryption(c, p, q);
	return 0;
}

//p:7 q:11 m:32