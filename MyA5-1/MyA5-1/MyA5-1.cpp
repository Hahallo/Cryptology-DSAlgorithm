// MyA5-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

typedef unsigned char byte;
class A5_1 {
public:
	unsigned long key;
	byte *keyStreamA = new byte[4];
	unsigned int frame = 0;//帧号
	unsigned int R1 = 0;//线性反馈移位寄存器R1(19) 
	unsigned int R2 = 0;//线性反馈移位寄存器R1(22)
	unsigned int R1OUT = 0x10;//5
	unsigned int R2OUT = 0x04;//4
	unsigned int R1MASK = 0x1F;//5bits,0..5
	unsigned int R2MASK = 0x04;// 4bits, 0..4
	//寄存器的钟控位置
	unsigned int R1MID = 0x03;//第3位
	unsigned int R2MID = 0x02;//第2位
	//寄存器的抽头位置
	unsigned int R1TAPS = 0x0c;//第3,4位
	unsigned int R2TAPS = 0x06;//第2,3位

public:
	//32位数的模2运算,二进制1的奇偶数
	unsigned int parity(unsigned int p)
	{//p为寄存器中抽头位置,求特征多项式f（x）
		p^= p>> 16;
		p^= p>> 8;
		p^= p>> 4;
		p^= p>> 2;
		p^= p>> 1;
		p&= 1;
		return p;
	}
	//择多原则
	int majority()
	{ 
		int sum = (((R1&R1MID) >> 3) & 1) & (((R2&R2MID) >> 2) & 1);
		return sum;
	}

	//处理寄存器运行状态(寄存器,抽头位置,掩码位)
	int clockOne(unsigned int r, unsigned  int taps, unsigned int mask )
	{//将寄存器移位
		unsigned int temp = r&taps;
		r = (r << 1)&mask;
		r |= parity(temp );
		return r;
	}
	//全部处理寄存器运行  
	void clockAll()
	{
		R1 = clockOne(R1, R1TAPS, R1MASK);
		R2 = clockOne(R2, R2TAPS, R2MASK);
	}
	//带钟控的全部处理寄存器运行状态
	void clockControl()
	{
		int temp = majority();
		if (temp  == ((R1 >> 3) & 1))//判断抽头3的值与temp相不相同
		{
			R1 = clockOne(R1, R1TAPS, R1MASK );
		}
		if (temp  == ((R2 >> 2) & 1))
		{
			R2 = clockOne(R2, R2TAPS, R2MASK );
		}
	}
	//密钥流的初始化
	void setKey()
	{
		int i = 0;
		int keyBit = 0;
		int frameBit = 0;
		for (;i < 9; i++)
		{
			keyBit  = (key >> i ) & 1;
			clockAll();//寄存器进行计数
			R1 ^= keyBit;
			R2 ^= keyBit;
		}
		for (i = 0;i < 22;i++)
		{
			frameBit = (frame >> i) & 1;
			clockAll();//寄存器进行计数
			R1 ^= frameBit;
			R2 ^= frameBit;
		}
	}
	//获得输出位
	int getOut() {
		int temp = parity(R1&R1OUT ) ^ parity(R2&R2OUT);
		return temp;
	}
	//获得密钥流
	 void getKey() {
		int  i ;
		for (i = 0; i < 30; i ++)
		{
			clockControl();
			keyStreamA[i / 8] |= (byte)(getOut() << (7 - (i & 7))); //字节从最高位存
		}

	}
	//密钥流的产生
	 void run()
	{
		setKey();
		getKey();
	}
	//构造函数(秘钥,帧号)
	 A5_1(unsigned long keyH, int frameH) {
		key = keyH;
		frame = frameH;
	}

	 //加密 
	  byte * encryption( unsigned char pt[],int len) {
		 int i = 0;
		 //数组长度<=15  
		 byte* cipherText= new byte[len];//密文      
		 for (i = 0; i < len; i ++)
		 {
			 cipherText[i] = (byte)(pt[i] ^ keyStreamA[i]);
		 }
		 return cipherText;
	 }
};
int main()
{
	unsigned long key = 412;
	int frame = 1;
	char data[512] = "彭溧阳";
	int len = strlen(data);
	A5_1 test(key, frame);
	test.run();
	cout << "明文为：" << data << endl;
	cout << "秘钥为：110011100" << endl;
	cout<<"加密之后为："<<test.encryption((unsigned char*)data,len)<<endl;
	return 0;
}