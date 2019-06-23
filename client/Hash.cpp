#define _CRT_SECURE_NO_WARNINGS
#include "Hash.h"
#include<iostream>
#include<string>
#include<string.h>
#include<openssl/md5.h>
#include<openssl/sha.h>
using namespace std;
Hash::Hash(HashType type)
{
	m_type = type;
	switch (type)
	{
	case T_MD5:
		md5Init();
		break;
	case T_SHA1:
		sha1Init();
		break;
	case T_SHA224:
		sha224Init();
		break;
	case T_SHA256:
		sha256Init();
		break;
	case T_SHA384:
		sha384Init();
		break;
	case T_SHA512:
		sha512Init();
		break;
	default:
		md5Init();
		break;
	}
}

void Hash::addData(string data)
{
	switch (m_type)
	{
	case T_MD5:
		md5AddData(data.data());
		break;
	case T_SHA1:
		sha1AddData(data.data());
		break;
	case T_SHA224:
		sha224AddData(data.data());
		break;
	case T_SHA256:
		sha256AddData(data.data());
		break;
	case T_SHA384:
		sha384AddData(data.data());
		break;
	case T_SHA512:
		sha512AddData(data.data());
		break;
	default:
		md5AddData(data.data());
		break;
	}
}

string Hash::result()
{
	string result = string();
	cout << "string()"<<result << endl;
	switch (m_type)
	{
	case T_MD5:
		result = md5Result();
		break;
	case T_SHA1:
		result = sha1Result();
		break;
	case T_SHA224:
		result = sha224Result();
		break;
	case T_SHA256:
		result = sha256Result();
		break;
	case T_SHA384:
		result = sha384Result();
		break;
	case T_SHA512:
		result = sha512Result();
		break;
	default:
		result = md5Result();
		break;
	}
	return result;
}

Hash::~Hash()
{
}

void Hash::md5Init()
{
	MD5_Init(&m_md5);

}

void Hash::md5AddData(const char * data)
{
	MD5_Update(&m_md5, data, strlen(data));
}

string Hash::md5Result()
{
	unsigned char md[MD5_DIGEST_LENGTH];
	char res[MD5_DIGEST_LENGTH * 2 + 1];
	MD5_Final(md, &m_md5);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, MD5_DIGEST_LENGTH*2+1);
}

void Hash::sha1Init()
{
	SHA1_Init(&m_sha1);
}

void Hash::sha1AddData(const char * data)
{
	SHA1_Update(&m_sha1, data, strlen(data));
}

string Hash::sha1Result()
{
	unsigned char md[SHA_DIGEST_LENGTH];
	char res[SHA_DIGEST_LENGTH * 2 + 1];
	SHA1_Final(md, &m_sha1);
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, SHA_DIGEST_LENGTH * 2 + 1);
}

void Hash::sha224Init()
{
	SHA224_Init(&m_sha224);
}

void Hash::sha224AddData(const char * data)
{
	SHA224_Update(&m_sha224, data, strlen(data));
}

string Hash::sha224Result()
{

	unsigned char md[SHA224_DIGEST_LENGTH];
	char res[SHA224_DIGEST_LENGTH * 2 + 1];
	SHA224_Final(md, &m_sha224);
	for (int i = 0; i < SHA224_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, SHA224_DIGEST_LENGTH * 2 + 1);
}

void Hash::sha256Init()
{
	SHA256_Init(&m_sha256);
}

void Hash::sha256AddData(const char * data)
{
	SHA256_Update(&m_sha256, data, strlen(data));
}

string Hash::sha256Result()
{
	unsigned char md[SHA256_DIGEST_LENGTH];
	char res[SHA256_DIGEST_LENGTH * 2 + 1];
	SHA256_Final(md, &m_sha256);
	for (int i = 0; i <  SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, SHA256_DIGEST_LENGTH * 2 + 1);
}

void Hash::sha384Init()
{
	SHA384_Init(&m_sha384);
}

void Hash::sha384AddData(const char * data)
{
	SHA384_Update(&m_sha384, data, strlen(data));
}

string Hash::sha384Result()
{
	unsigned char md[SHA384_DIGEST_LENGTH];
	char res[SHA384_DIGEST_LENGTH * 2 + 1];
	SHA384_Final(md, &m_sha384);
	for (int i = 0; i < SHA384_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, SHA384_DIGEST_LENGTH * 2 + 1);
}

void Hash::sha512Init()
{
	SHA512_Init(&m_sha512);
}

void Hash::sha512AddData(const char * data)
{
	SHA512_Update(&m_sha512,data,strlen(data));
}

string Hash::sha512Result()
{
	unsigned char md[SHA512_DIGEST_LENGTH];
	char res[SHA512_DIGEST_LENGTH * 2 + 1];
	SHA512_Final(md, &m_sha512);
	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	return string(res, SHA512_DIGEST_LENGTH * 2 + 1);
}
