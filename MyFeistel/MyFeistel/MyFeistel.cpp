// MyFeistel.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;

const int Nr = 4;//��Ҫ4�ּ���
class Feistel {
private:
	unsigned char key[4];
	int nr;
public:
	Feistel(unsigned char*keyH, int n) {//���캯��
		for (int i = 0;i < n;i++)
		{
			key[i] = keyH[i];
		}
		nr = n;
	}
	int change(unsigned char*p,int i)//���ַ���ת��Ϊ����
	{
		int r=0;
		int t=1;
		int a=0;
		unsigned char b = p[i];
		for (int j = 0;j < 8;j++)
		{
			//b = >>1;
			r+=((b>>j) & 0x01)*t;
			t *= 2;
		}
		return r;
	}

	int E(int p1)//R=�٢ڢۢܣ� E(R) = �ڢ٢ڢۢܢ�
	{
		unsigned char a = (p1 >> 2) & 0x01;
		unsigned char b = (p1 >> 3) & 0x01;
		int r = p1;
		r <<= 1;
		r |= a;
		r |= (b << 5);
		return r;
	}

	int S(int p2)//S(�٢ڢۢܢݢ�)=�٢ڢۢ�
	{
		p2 >>= 2;
		return p2;
	}

	int P(int p3)//P(�٢ڢۢ�)= �ڢܢ٢�
	{
		int a = p3 & 0x01;
		int b = (p3 >> 1) & 0x01;
		int c = (p3 >> 2) & 0x01;
		int d = (p3 >> 3) & 0x01;
		int r = 0;
		r |= c;
		r |= (a << 1);
		r |= (d << 2);
		r |= (b << 3);
		return r;
	}

	int f(int p1,unsigned char* key)//�ֺ���f=P(S ( E(R) + Ki)),  i=1,2,3,4 
	{
		int r = p1&0x0f;
		int l = p1 >> 4;
		int res;
		int temp;
		for (int i = 0;i <nr;i++)
		{
			temp = r;
			r= P(S(E(temp) ^ key[i]));
			l = temp;
		}
		res = (l << 4) |r;
		return res;
	}
	unsigned char*encription(unsigned char*p,int len)
	{
		unsigned char *c = new unsigned char[len];
		for (int j = 0;j < len;j++)
		{
			int p1 = change(p, j);
			c[j] = f(p1, key);
		}
		return c;
	}
};
int main()
{
	unsigned char p[7] = "������";
	unsigned char key[4] = { 63,56,7,0 };
	Feistel test(key, Nr);
	cout << "����Ϊ��" << p<<endl;
	cout <<"����Ϊ��"<<test.encription(p,7) <<endl;
    return 0;
}

