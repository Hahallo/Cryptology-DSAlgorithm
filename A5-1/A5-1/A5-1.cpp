// A5-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>>

using namespace std;

class A5_1
{
private:
	byte key[] = new byte[8];//密钥
	byte keyStreamA[] = new byte[15];//加密密钥流 
	byte keyStreamB[] = new byte[15];//解密密钥流  
	int  frame  = 0;//帧号 
	int  R1  = 0;//线性反馈移位寄存器R1(19) 
	int  R2  = 0;//线性反馈移位寄存器R2(22) 
	int R3  = 0;//线性反馈移位寄存器R3(23)  
				//寄存器的输出位数 
	int  R1OUT  = 0x040000;//19 
	int R2OUT  = 0x200000;//22  
	int R3OUT  = 0x400000;//23  //寄存器的掩码位 
	int R1MASK  = 0x07FFFF;//19 bits,0..18   
	int R2MASK  = 0x3FFFFF;//22 bits,0..21  
	int R3MASK  = 0x7FFFFF;//23 bits,0..22   
						   //寄存器的钟控位置 

	int R1MID  = 0x000100;//第8位
	int R2MID  = 0x000400;//第10位   
	int R3MID  = 0x000400;//第10位  
						  //寄存器的抽头位置 
	int R1TAPS  = 0x072000;//第13,16,17,18位  
	int R2TAPS  = 0x300000;//第20,21位  
	int R3TAPS  = 0x700080;//第7,20,21,22位

						   //构造函数(秘钥, 帧号)  
	A5_1(String key, int frame ) {
		this.key  = key.getBytes();
		this.frame  = frame;
	}
	//32位数的模2运算,二进制1的奇偶数 
	private int parity(int p )
	{
		p  ^= p  >> 16;
		p  ^= p  >> 8;
		p  ^= p  >> 4;
		p  ^= p  >> 2;
		p  ^= p  >> 1;
		p  &= 1;
		return p;
	}
	//择多原则 
	private int majority()
	{
		int sum  = (((R1&R1MID) >> 8) & 1) + (((R2&R2MID) >> 10) & 1) + (((R3&R3MID) >> 10) & 1);
		if (sum  >= 2) {
			return 1;
		}
		return 0;
	}
	//处理寄存器运行状态(寄存器, 抽头位置, 掩码位 ) 
	private int clockOne(int r, int taps, int mask )
	{
		int temp  = r&taps;
		r  = (r << 1)&mask;
		r  |= parity(temp );
		return r;
	}
	//全部处理寄存器运行  
	private void clockAll()
	{
		R1  = clockOne(R1, R1TAPS, R1MASK );
		R2  = clockOne(R2, R2TAPS, R2MASK );
		R3  = clockOne(R3, R3TAPS, R3MASK );
	}
	//带钟控的全部处理寄存器运行状态  
	private void clockControl()
	{
		int temp  = majority();
		if (temp  == ((R1 >> 8) & 1))
		{
			R1  = clockOne(R1, R1TAPS, R1MASK );
		}
		if (temp  == ((R2 >> 10) & 1))
		{
			R2  = clockOne(R2, R2TAPS, R2MASK );
		}
		if (temp  == ((R3 >> 10) & 1))
		{
			R3  = clockOne(R3, R3TAPS, R3MASK );
		}
	}
	//密钥流的初始化  
	private void setKey()
	{
		int i  = 0;
		int keyBit  = 0;
		int frameBit  = 0;
		for (i < 64; i ++)
		{
			keyBit  = (key[i / 8] >> (i & 7)) & 1;
			clockAll();    //寄存器进行计数 
			R1  ^= keyBit;
			R2  ^= keyBit;
			R3  ^= keyBit;
		}
		for (i  = 0; i < 22; i ++)
		{
			frameBit  = (frame  >> i ) & 1;
			clockAll();    //寄存器进行计数 
			R1  ^= frameBit;
			R2  ^= frameBit;
			R3  ^= frameBit;
		}
		for (i  = 0; i < 100; i ++)
		{
			clockControl();
		}
	}
	//获得输出位 
	private int getOut() {

		int temp  = parity(R1&R1OUT ) ^ parity(R2&R2OUT ) ^ parity(R3&R3OUT );
		return temp;
	}
	//获得密钥流 
	private void getKey() {
		int i  = 0;
		for (i  = 0; i < 114; i ++)
		{
			clockControl();


			keyStreamA[i / 8] |= (byte)(getOut() << (7 - (i & 7))) //字节从最高位存   
		}
		for (i  = 0; i < 114; i ++)
		{
			clockControl();
			keyStreamB[i / 8] |= (byte)(getOut() << (7 - (i & 7)));
		}
	}
	//密钥流的产生  
	public void run()
	{
		setKey();
		getKey();
	}
	//以16进制输出明文和密文  
	public void printHexText(byte pt[])
	{
		System.out.println("明文：");

		for (int i = 0; i < pt.length; i ++)
		{
			System.out.print(Integer.toHexString(pt[i] & 0xFF) + ", ");
		}
		byte ct[] = encryption(pt );
		System.out.println("\n密文：");
		for (int i = 0; i < ct.length; i ++) {
			System.out.print(Integer.toHexString(ct[i] & 0xFF) + ", ");
		}
		System.out.println("\n");
	}  //加密 
	public byte[] encryption(byte pt[]) {
		int i  = 0;
		int len  = pt.length;//数组长度<=15  

		byte cipherText[] = new byte[len];//密文      
		for (i = 0; i < len; i ++)
		{
			cipherText[i] = (byte)(pt[i] ^ keyStreamA[i]);
		}
		return cipherText;
	}
}