#pragma once
#include<iostream>
#include<string>
#include<openssl/md5.h>
#include<openssl/sha.h>
using namespace std;
enum HashType
{
	T_MD5,
	T_SHA1,
	T_SHA224,
	T_SHA256,
	T_SHA384,
	T_SHA512,
};
class Hash
{
public:
	Hash(HashType type);
	void addData(string data);
	string result();
	~Hash();
private:
	//md5
	void md5Init();
	void md5AddData(const char* data);
	string md5Result();
	//sha1
	void sha1Init();
	void sha1AddData(const char* data);
	string sha1Result();
	//sha224
	void sha224Init();
	void sha224AddData(const char* data);
	string sha224Result();
	//SHA256
	void sha256Init();
	void sha256AddData(const char* data);
	string sha256Result();
	//SHA384
	void sha384Init();
	void sha384AddData(const char* data);
	string sha384Result();
	//SHA512
	void sha512Init();
	void sha512AddData(const char* data);
	string sha512Result();

private:
	HashType m_type;
	MD5_CTX m_md5;
	SHA_CTX m_sha1;
	SHA256_CTX m_sha224;
	SHA256_CTX m_sha256;
	SHA512_CTX m_sha384;
	SHA512_CTX m_sha512;
};

