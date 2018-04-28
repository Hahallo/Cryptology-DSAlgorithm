// RABIN数字签名.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

class RABINDS {
public:
	/*扩展的欧几里得算法*/
	int EEuclid(int *a, int *b)
	{
		int R = *a, r = *b;
		int S = 1, s = 0, T = 0, t = 1;
		int q = R / r;
		int i, j, k;
		while (r)
		{
			i = R - q*r;
			j = S - q*s;
			k = T - q*t;
			R = r;
			S = s;
			T = t;
			r = i;
			s = j;
			t = k;
			if (r)
				q = R / r;
			else
				break;
		}
		*a = abs(S);
		*b = abs(T);
		return 0;
	}
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
	/*签名函数*/
	int Sign(int p,int q,int c1)
	{
		int a = p;
		int b = q;
		int p1 = (p + 1) / 4;
		int q1 = (q + 1) / 4;
		int n = p*q;
		int u, v;
		int m1, m2;
		EEuclid(&a, &b);
		u = squra(c1, p1, p);
		v = squra(c1, q1, q);
		m1 = (u*b*q + v*a*p) % n;
		m2 = (u*b*q - v*a*p) % n;
		abs(n - abs(m1));
		abs(n - abs(m2));
		return m1;
	}
};

int main()
{
	int p, q,m;
	cout << "请输入两个大素数p和q：";
	cin >> p >> q;//p,q是大素数 m是p，q的平方剩余
	cout << "请输入待签名的m：";
	cin >> m;
	RABINDS test;
	int s = test.Sign(p, q, m);//得到签名
	cout<<m<<"的签名是："<<s<<endl;
	cout << "调用验证函数，结果为：";
	if ((s*s) % (p*q) == m)cout << "验证通过!" << endl;//验证签名
	else cout << "验证失败！" << endl;
    return 0;
}
// p:7 q:11 待签名c1:23 
