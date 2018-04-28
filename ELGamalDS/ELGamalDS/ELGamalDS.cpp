// ELGamalDS.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

class ELGamalDs {
private:
	//����
	int m_p;
	int m_g;
	int Ya;
	//˽Կ
	int m_a;
	//ǩ��
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
	/*��Կ����*/
	void Generatingkey(int a) {
		m_a = a;
		Ya = square(m_g, m_a, m_p);
	}
	/*ǩ������*/
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
	/*ȡk����*/
	int Getk(int k) {
		for (int i = 1;i <= m_p - 2;i++)
		{
			if (k*i % (m_p - 1) == 1)return i;
		}
		return 1;
	}
	/*���ǩ��*/
	void show_s() {
		cout <<"ǩ��Ϊ��"<< "r:" << r << ",s:" << s << endl;
	}
	/*��֤ǩ��*/
	bool Verify(int m) {
		if (fmod(pow(Ya, r)*pow(r, s),m_p) == fmod( pow(m_g, m),m_p))return true;
		else return false;
	}
};
int main()
{
	int p;//������
	int g;//�˷���Zq������Ԫg
	int m;//��ǩ������Ϣ
	int x;//˽Կ
	int k;//���ѡȡ������k
	cout << "����һ����������";
	cin >> p;
	cout << "����˷�ȺZq������Ԫg��";
	cin >> g;
	cout << "�����ǩ������Ϣ��";
	cin >> m;
	cout << "�������ѡȡ��˽Կ��";
	cin >> x;
	cout << "�������ѡȡ������k��";
	cin >> k;
	ELGamalDs test(p, g);//p=11��g=2
	test.Generatingkey(x);//˽Կx=8
	test.Sign(m,k);//��Ϣm=5���������k=9
	test.show_s();//m=5��ǩ��
	cout << "��֤���Ϊ��";
	if (test.Verify(m))cout << "��֤ͨ��!" << endl;//��֤ǩ��
	else cout << "��֤ʧ��!" << endl;
    return 0;
}

