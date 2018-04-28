// ELGamal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class ELGamal {
private:
	//公钥
	int m_p;
	int m_g;
	int Ya;
	//密文
	int m_u;
	int m_v;
	//私钥
	int a;
	//随机整数
	int k;
public:
	ELGamal(int p,int g) {
		m_p = p;
		m_g = g;
	}
	/*计算m的e次方模n*/
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
	/*生成密钥和公钥*/
	void Generatingkey() {
		srand((unsigned)time(NULL));		//随机数种子
		a = 2 + rand() % (m_p - 4);		//随机选择2<=r<=p-4
		Ya = square(m_g, a, m_p);

	}
	/*加密函数*/
	void Encryption(int m) {
		srand((unsigned)time(NULL));		//随机数种子
		k = 2 + rand() % (m_p - 4);
		m_u = square(m_g, k, m_p);
		m_v = m*square(Ya, k, m_p);
	}
	/*输出密文*/
	void showm() {
		cout <<"u："<< m_u << ",v：" << m_v << endl;
	}
	/*解密函数*/
	int  Decryption() {
		return m_v / square(m_u, a, m_p);
	}

};

int main()
{
	int p;//大素数
	int g;//乘法群Zp的生成元g
	int m;
	cout<< "输入一个大素数：";
	cin >> p;
	cout << "输入乘法群Zp的生成元g：";
	cin >> g;
	cout << "输入待加密的消息：";
	cin >> m;
	ELGamal test(p, g);
	test.Generatingkey();
	test.Encryption(m);
	cout << "明文为：" <<m<< endl;
	cout << "密文为：";
	test.showm();
	cout <<"调用解密函数，解密得到明文为：" <<test.Decryption() << endl;
    return 0;
}

//p:2597 g:2 m:素数