// ELGamalDS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

class ELGamalDs {
private:
	//公开
	int m_p;
	int m_g;
	int Ya;
	//私钥
	int m_a;
	//签名
	int r;
	int s;
public:
	ELGamalDs(int p, int g) {
		m_p = p;
		m_g = g;
	}
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
	/*密钥生成*/
	void Generatingkey(int a) {
		m_a = a;
		Ya = square(m_g, m_a, m_p);
	}
	/*签名生成*/
	void Sign(int m,int k) {
		r = square(m_g, k, m_p);
		s = ((m - m_a*r) *Getk(k)) % (m_p - 1);
		int i = 1;
		while (s < 0)
		{
			s += (m_p - 1)*i;
			++i;
		}
	}
	/*取k的逆*/
	int Getk(int k) {
		for (int i = 1;i <= m_p - 2;i++)
		{
			if (k*i % (m_p - 1) == 1)return i;
		}
		return 1;
	}
	/*输出签名*/
	void show_s() {
		cout <<"签名为："<< "r:" << r << ",s:" << s << endl;
	}
	/*验证签名*/
	bool Verify(int m) {
		if (fmod(pow(Ya, r)*pow(r, s),m_p) == fmod( pow(m_g, m),m_p))return true;
		else return false;
	}
};
int main()
{
	int p;//大素数
	int g;//乘法器Zq的生成元g
	int m;//待签名的消息
	int x;//私钥
	int k;//随机选取的整数k
	cout << "输入一个大素数：";
	cin >> p;
	cout << "输入乘法群Zq的生成元g：";
	cin >> g;
	cout << "输入待签名的消息：";
	cin >> m;
	cout << "输入随机选取的私钥：";
	cin >> x;
	cout << "输入随机选取的整数k：";
	cin >> k;
	ELGamalDs test(p, g);//p=11，g=2
	test.Generatingkey(x);//私钥x=8
	test.Sign(m,k);//消息m=5，随机整数k=9
	test.show_s();//m=5的签名
	cout << "验证结果为：";
	if (test.Verify(m))cout << "验证通过!" << endl;//验证签名
	else cout << "验证失败!" << endl;
    return 0;
}

