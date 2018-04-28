// RSADS.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class RSADS {
private:
	int m_n;//��Կ�������������ĳ˻�
	int m_e;//��Կ�����ѡȡ������
	int m_d;//˽Կ

public:
	/*������Կ����*/
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
	/*ǩ������*/
	int Sign(int m)
	{
		return square(m, m_d, m_n);
	}
	/*��֤����*/
	int Verify(int c)
	{
		return square(c, m_e,m_n);
	}
	/*��չ��ŷ����ó���*/
	int ExtendedEuclid(int a, int b)//��չ��ŷ������㷨
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
	/*�����Լ��*/
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
	/*��m��e�η�ģn*/
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
	cout << "����������������p��q��" << endl;
	cin >> p >> q;
	cout << "����Ҫǩ������Ϣ��";
	cin >> m;
	test.KeyGen(p, q);
	int ds = test.Sign(m);
	cout << m<<"��ǩ����:" << ds<< endl;
	if (test.Verify(ds) == m)cout << "��֤ͨ��!"<<endl;
	else cout << "��֤ʧ��!" << endl;
    return 0;
}

//p:11 q:13 m:24 c=7 

