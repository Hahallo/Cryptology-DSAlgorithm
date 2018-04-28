// ELGamal.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class ELGamal {
private:
	//��Կ
	int m_p;
	int m_g;
	int Ya;
	//����
	int m_u;
	int m_v;
	//˽Կ
	int a;
	//�������
	int k;
public:
	ELGamal(int p,int g) {
		m_p = p;
		m_g = g;
	}
	/*����m��e�η�ģn*/
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
	/*������Կ�͹�Կ*/
	void Generatingkey() {
		srand((unsigned)time(NULL));		//���������
		a = 2 + rand() % (m_p - 4);		//���ѡ��2<=r<=p-4
		Ya = square(m_g, a, m_p);

	}
	/*���ܺ���*/
	void Encryption(int m) {
		srand((unsigned)time(NULL));		//���������
		k = 2 + rand() % (m_p - 4);
		m_u = square(m_g, k, m_p);
		m_v = m*square(Ya, k, m_p);
	}
	/*�������*/
	void showm() {
		cout <<"u��"<< m_u << ",v��" << m_v << endl;
	}
	/*���ܺ���*/
	int  Decryption() {
		return m_v / square(m_u, a, m_p);
	}

};

int main()
{
	int p;//������
	int g;//�˷�ȺZp������Ԫg
	int m;
	cout<< "����һ����������";
	cin >> p;
	cout << "����˷�ȺZp������Ԫg��";
	cin >> g;
	cout << "��������ܵ���Ϣ��";
	cin >> m;
	ELGamal test(p, g);
	test.Generatingkey();
	test.Encryption(m);
	cout << "����Ϊ��" <<m<< endl;
	cout << "����Ϊ��";
	test.showm();
	cout <<"���ý��ܺ��������ܵõ�����Ϊ��" <<test.Decryption() << endl;
    return 0;
}

//p:2597 g:2 m:����