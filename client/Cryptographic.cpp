#include "Cryptographic.h"
#include<openssl/rsa.h>
#include<openssl/err.h>

Cryptographic::Cryptographic()
{
	m_publicKey = RSA_new();
	m_privateKey = RSA_new();
}

Cryptographic::Cryptographic(string filename, bool isPrivate)
{
	m_publicKey = RSA_new();
	m_privateKey = RSA_new();
	if (isPrivate)
	{
		initPrivateKey(filename);
	}
	else
	{
		initPublicKey(filename);
	}
}

Cryptographic::~Cryptographic()
{
	RSA_free(m_publicKey);
	RSA_free(m_privateKey);
}

void Cryptographic::generateKeyFile(int bits, string pub, string pri)
{
	RSA* r = RSA_new();
	//生成RSA密钥对
	//创建bignum对象
	BIGNUM* e = BN_new();
	//初始化bignum对象
	BN_set_word(e, 345655);
	RSA_generate_key_ex(r, 1028, e, NULL);
	//创建bio文件对象
	BIO* pubIO = BIO_new_file(pub.data(), "w");
	//公钥以pem格式写入到文件中
	PEM_write_bio_RSAPublicKey(pubIO, r);
	//缓冲中的数据刷到文件中
	BIO_flush(pubIO);
	BIO_free(pubIO);

	//创建bio文件对象
	BIO* priIO = BIO_new_file(pri.data(), "w");
	//公钥以pem格式写入到文件中
	PEM_write_bio_RSAPrivateKey(priIO, r,NULL,NULL,0,NULL,NULL);
	//缓冲中的数据刷到文件中
	BIO_flush(priIO);
	BIO_free(priIO);
	//得到公钥和私钥
	m_privateKey = RSAPrivateKey_dup(r);
	m_publicKey = RSAPublicKey_dup(r);
	//释放资源
	BN_free(e);
	RSA_free(r);
}

string Cryptographic::rsaPubKeyEncrypt(string data)
{
	//计算公钥的长度
	int keyLen = RSA_size(m_publicKey);
	char* encode = new char[keyLen + 1];
	int ret=RSA_public_encrypt(data.size(), (const unsigned char*)data.data()
		, (unsigned char* )encode, m_publicKey, RSA_PKCS1_PADDING);
	string retStr = string();
	if (ret>=0)
	{
		//加密成功
		retStr = string(encode, ret);
	}
	//释放资源
	delete[]encode;
	return retStr;
}

string Cryptographic::rsaPriKeyDecrypt(string encData)
{
	//计算私钥的长度
	int keyLen = RSA_size(m_privateKey);
	char* decode = new char[keyLen + 1];
	int ret = RSA_private_encrypt(encData.size(), (const unsigned char*)encData.data()
		, (unsigned char*)decode, m_privateKey, RSA_PKCS1_PADDING);
	string retStr = string();
	if (ret >= 0)
	{
		//解密成功
		retStr = string(decode, ret);
	}
	//释放资源
	delete[]decode;
	return retStr;
}

string Cryptographic::rsaSign(string data, SignLevel level)
{
	unsigned int len;
	char * signbuf = new char[RSA_size(m_privateKey) + 1];
	RSA_sign(level, (const unsigned char*)data.data(), data.size()
		, (unsigned char*)signbuf, &len, m_privateKey);
	string retStr = string(signbuf, len);
	return retStr;
}


bool Cryptographic::rsaVerify(string data, string signData, SignLevel level)
{
	//验证签名
	int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
		(const unsigned char*)signData.data(), signData.size(), m_publicKey);
	if (ret==-1)
	{
		return false;
	}
	return true;
}
//得到公钥
bool Cryptographic::initPublicKey(string pubfile)
{
	//通过biO读文件
	BIO* pubBio = BIO_new_file(pubfile.data(), "'r");
	//将bio的pem数据读出
	if (PEM_read_bio_RSAPublicKey(pubBio, &m_publicKey, NULL, NULL)==NULL);
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(pubBio);
	return true;
}
//得到私钥
bool Cryptographic::initPrivateKey(string prifile)
{
	//通过biO读文件
	BIO* priBio = BIO_new_file(prifile.data(), "'r");
	//将bio的pem数据读出
	if (PEM_read_bio_RSAPrivateKey(priBio, &m_privateKey, NULL, NULL) == NULL);
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(priBio);
	return true;
 
}
