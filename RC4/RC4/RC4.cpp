// RC4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

class RC4 {
public:
	vector<unsigned char> keystream;//存储密钥流
	void KSA(unsigned char S[], unsigned  char K[], int Keylen)//初始化
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
	void PRGA(unsigned char S[], int len)//产生密钥流
	{
		int i = 0, j = 0;
		int k = 0;
		while (k<len)
		{
			i = (i + 1) % 256;
			j = (j + S[i]) % 256;
			swap(S[i], S[j]);
			int t = (S[i] + S[j]) % 256;
			keystream.push_back(S[t]);//存密钥流
			k++;
		}
	}
};

int main()
{
	char data[512] = "你的滑板鞋";
	unsigned char c[512] = { 0 };
	unsigned char S[256] = { 0 };
	char key[256] = "庞麦郎";
	int Keylen = strlen(key);
	int datalen = strlen(data);
	strlen(key);
	cout << "明文为：" << data << endl;
	cout << "秘钥为：" << key << endl;
	RC4 test;
	test.KSA(S, (unsigned char*)key, Keylen);
	test.PRGA((unsigned char*)S, datalen);
	
	cout << "密钥流为：" ;
	for (unsigned i=0;i<test.keystream.size();i++)
	{
		cout << test.keystream[i];
	}
	for (unsigned i = 0;i < strlen(data);i++)
	{
		c[i]=  (unsigned char)data[i] ^ test.keystream[i];
	}
	cout << endl << "加密之后为:" << c << endl;
	cout << "解密之后为:";
	for (unsigned i = 0;i < strlen(data);i++)
	{
		cout << (unsigned char)(c[i] ^ test.keystream[i]);
	}
	cout << endl;
    return 0;
}

