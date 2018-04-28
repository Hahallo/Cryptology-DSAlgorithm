// RC4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

class RC4 {
public:
	vector<unsigned char> keystream;//�洢��Կ��
	void KSA(unsigned char S[], unsigned  char K[], int Keylen)//��ʼ��
	{
		char T[256] = { 0 };
		for (int i = 0;i<256;i++)
		{
			S[i] = i;
			T[i] = K[i%Keylen];
		}
		int j = 0;
		for (int i = 0;i < 256;i++)
		{
			j = (j + S[i] + T[i]) % 256;
			swap(S[i], S[j]);
		}
	}
	void PRGA(unsigned char S[], int len)//������Կ��
	{
		int i = 0, j = 0;
		int k = 0;
		while (k<len)
		{
			i = (i + 1) % 256;
			j = (j + S[i]) % 256;
			swap(S[i], S[j]);
			int t = (S[i] + S[j]) % 256;
			keystream.push_back(S[t]);//����Կ��
			k++;
		}
	}
};

int main()
{
	char data[512] = "�й����ʴ�ѧ���人��";
	unsigned char c[512] = { 0 };
	unsigned char S[256] = { 0 };
	char key[256] = "������";
	int Keylen = strlen(key);
	int datalen = strlen(data);
	strlen(key);
	cout << "����Ϊ��" << data << endl;
	cout << "��ԿΪ��" << key << endl;
	RC4 test;
	test.KSA(S, (unsigned char*)key, Keylen);
	test.PRGA((unsigned char*)S, datalen);
	
	cout << "��Կ��Ϊ��" ;
	for (unsigned i=0;i<test.keystream.size();i++)
	{
		cout << test.keystream[i];
	}
	for (unsigned i = 0;i < strlen(data);i++)
	{
		c[i]=  (unsigned char)data[i] ^ test.keystream[i];
	}
	cout << endl << "����֮��Ϊ:" << c << endl;
	cout << "����֮��Ϊ:";
	for (unsigned i = 0;i < strlen(data);i++)
	{
		cout << (unsigned char)(c[i] ^ test.keystream[i]);
	}
	cout << endl;
    return 0;
}

