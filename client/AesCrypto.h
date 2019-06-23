#pragma once
#include<iostream>	
#include<openssl/aes.h>
#include<string>
using namespace std;

class AesCrypto
{
public:
	//��ʹ��16byte,24byte,32byte����Կ
	AesCrypto(string key);
	//����
	string aesCBCEncrypt(string text);
	//����
	string aesCBCDecrypt(string encStr);
	
	~AesCrypto();
private:
	string aesCrypto(string data, int crypto);
	void generateTvec(unsigned char* ivec);

private:
	AES_KEY m_encKey;
	AES_KEY m_decKey;
	string m_key;//��Կ
	
};

