#include "AesCrypto.h"
#include<iostream>
AesCrypto::AesCrypto(string key)
{
	if (key.size()==16||key.size()==24||key.size()==32)
	{
	const unsigned char* askey=	(const unsigned char*)key.data();
		
	AES_set_encrypt_key(askey, key.size() * 8, &m_encKey);
	AES_set_decrypt_key(askey, key.size() * 8, &m_decKey);
	m_key = key;
	}
}

string AesCrypto::aesCBCEncrypt(string text)
{
	return aesCrypto(text, AES_ENCRYPT);
}

string AesCrypto::aesCBCDecrypt(string encStr)
{
	return aesCrypto(encStr, AES_DECRYPT);
}

AesCrypto::~AesCrypto()
{
}

string AesCrypto::aesCrypto(string data, int crypto)
{
	AES_KEY* key = crypto == AES_ENCRYPT ? &m_encKey : &m_decKey;
	int length = 0;
	if (data.size()%16!=0)
	{
	 length = (data.size() % 16 + 1) * 16;
	}
	else
	{
		length = data.size()+1;
	}
	 char* out =  new char[length];
	unsigned char  ivec[AES_BLOCK_SIZE];
	generateTvec(ivec);
	AES_cbc_encrypt((const unsigned char*)data.c_str(), 
		(unsigned char*)out, length, key, ivec, crypto);
	string retStr = string(out);
	delete[]out;
	return string(retStr);
}

void AesCrypto::generateTvec(unsigned char * ivec)
{
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
	{
		ivec[i] = m_key.at(AES_BLOCK_SIZE - i - 1);
	}
}
