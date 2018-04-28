// Lamport.cpp : �������̨Ӧ�ó������ڵ㡣
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
	vector<int>skey ;//˽Կ
	vector<int>pkey ;//��Կ
	int m_a;
	int m_b;
public:
	/*ȷ��hash����f(x)= a^x mod b*/
	LamportDS(int a, int b) {
		m_a = a;
		m_b = b;
	}
	/*�õ���Կ�͹�Կ*/
	void Getkey(int k) {
		srand((unsigned)time(NULL));
		for (int i = 0;i <2*k;i++)
		{
			int temp= rand() % m_b;//���ȡ2*k��0��m_b�������
			skey.push_back(temp);
			pkey.push_back(Hash(temp));
		}
	}
	/*������*/
	int Hash(int y) {
		return square(m_a,y,m_b);
	}
	/*ǩ������*/
	vector<int>Sign(string m) {

		int length = m.size();
		vector<int>sign(length);
		for (int i = 0;i < length;i++)
		{
			sign[i] = skey[2 * i + m[i] - '0'];//ǩ��
		}
		return sign;
	}
	/*��֤����*/
	bool Verify(string m,vector<int>sign) {
		int length = m.size();
		for (int i = 0;i < length;i++)
		{
			if (Hash(sign[i]) != pkey[2 * i + m[i] - '0'])//��֤
				return false;
		}
		return true;
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
	LamportDS test(3, 7879);
	test.Getkey(3);//���һ��2*3���ȵ�˽Կ
	string m = "010";//����
	cout << "����Ϊ��" << m<<endl;
	vector<int>s=test.Sign(m);//ǩ��
	cout << "ǩ��Ϊ��";
	for (int i : s)
	{
		cout << i << ",";
	}
	cout << endl << "��֤���Ϊ��";
	if (test.Verify(m, s))cout <<"��֤ͨ��!" << endl;
	else cout << "��֤ʧ��!" << endl;
    return 0;
}

