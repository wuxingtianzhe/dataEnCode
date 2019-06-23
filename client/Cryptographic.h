﻿#pragma once
#include<iostream>
#include<openssl/rsa.h>
#include<openssl/pem.h>
using namespace std;
enum SignLevel
{
	Level1 = NID_md5,
	Level2=NID_sha1,
	Level3=NID_sha224,
	Level4=NID_sha256,
	Level5=NID_sha384,
	Level6=NID_sha512
};
class Cryptographic
{
public:
	Cryptographic();
	Cryptographic(string filename, bool isPrivate = true);
	~Cryptographic();
	//生成RSA密钥对
	void generateKeyFile(int bits, string pub = "public.pem", string pri = "private.pem");

	//公钥加密
	string rsaPubKeyEncrypt(string data);
	//私钥解密
	string rsaPriKeyDecrypt(string  encData);
	//使用RSA签名
	string rsaSign(string data, SignLevel level = Level3);

	//使用RSA验证签名
	bool rsaVerify(string data, string signData, SignLevel level = Level3);
private:
	string toBase64(const char* str, int len);
	// base64解码
	char* fromBase64(string str);
	//得到公钥
	bool initPublicKey(string pubfile);
	//得到私钥
	bool initPrivateKey(string prifile);
	//base64����
	string toBase64(const char* str, int len);
	//base64����
	char* fromBase64(string str);
private:
	RSA * m_publicKey;//公钥
	RSA*  m_privateKey;//私钥
};

