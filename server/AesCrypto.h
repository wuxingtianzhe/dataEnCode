#pragma once
#include<iostream>	
#include<openssl/aes.h>
#include<string>
using namespace std;

class AesCrypto
{
public:
	//可使用16byte,24byte,32byte的密钥
	AesCrypto(string key);
	//加密
	string aesCBCEncrypt(string text);
	//解密
	string aesCBCDecrypt(string encStr);
	
	~AesCrypto();
private:
	string aesCrypto(string data, int crypto);
	void generateTvec(unsigned char* ivec);

private:
	AES_KEY m_encKey;
	AES_KEY m_decKey;
	string m_key;//密钥
	
};

