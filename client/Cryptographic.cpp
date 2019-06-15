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
	//����RSA��Կ��
	//����bignum����
	BIGNUM* e = BN_new();
	//��ʼ��bignum����
	BN_set_word(e, 345655);
	RSA_generate_key_ex(r, 1028, e, NULL);
	//����bio�ļ�����
	BIO* pubIO = BIO_new_file(pub.data(), "w");
	//��Կ��pem��ʽд�뵽�ļ���
	PEM_write_bio_RSAPublicKey(pubIO, r);
	//�����е�����ˢ���ļ���
	BIO_flush(pubIO);
	BIO_free(pubIO);

	//����bio�ļ�����
	BIO* priIO = BIO_new_file(pri.data(), "w");
	//��Կ��pem��ʽд�뵽�ļ���
	PEM_write_bio_RSAPrivateKey(priIO, r,NULL,NULL,0,NULL,NULL);
	//�����е�����ˢ���ļ���
	BIO_flush(priIO);
	BIO_free(priIO);
	//�õ���Կ��˽Կ
	m_privateKey = RSAPrivateKey_dup(r);
	m_publicKey = RSAPublicKey_dup(r);
	//�ͷ���Դ
	BN_free(e);
	RSA_free(r);
}

string Cryptographic::rsaPubKeyEncrypt(string data)
{
	//���㹫Կ�ĳ���
	int keyLen = RSA_size(m_publicKey);
	char* encode = new char[keyLen + 1];
	int ret=RSA_public_encrypt(data.size(), (const unsigned char*)data.data()
		, (unsigned char* )encode, m_publicKey, RSA_PKCS1_PADDING);
	string retStr = string();
	if (ret>=0)
	{
		//���ܳɹ�
		retStr = string(encode, ret);
	}
	//�ͷ���Դ
	delete[]encode;
	return retStr;
}

string Cryptographic::rsaPriKeyDecrypt(string encData)
{
	//����˽Կ�ĳ���
	int keyLen = RSA_size(m_privateKey);
	char* decode = new char[keyLen + 1];
	int ret = RSA_private_encrypt(encData.size(), (const unsigned char*)encData.data()
		, (unsigned char*)decode, m_privateKey, RSA_PKCS1_PADDING);
	string retStr = string();
	if (ret >= 0)
	{
		//���ܳɹ�
		retStr = string(decode, ret);
	}
	//�ͷ���Դ
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
	//��֤ǩ��
	int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
		(const unsigned char*)signData.data(), signData.size(), m_publicKey);
	if (ret==-1)
	{
		return false;
	}
	return true;
}
//�õ���Կ
bool Cryptographic::initPublicKey(string pubfile)
{
	//ͨ��biO���ļ�
	BIO* pubBio = BIO_new_file(pubfile.data(), "'r");
	//��bio��pem���ݶ���
	if (PEM_read_bio_RSAPublicKey(pubBio, &m_publicKey, NULL, NULL)==NULL);
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(pubBio);
	return true;
}
//�õ�˽Կ
bool Cryptographic::initPrivateKey(string prifile)
{
	//ͨ��biO���ļ�
	BIO* priBio = BIO_new_file(prifile.data(), "'r");
	//��bio��pem���ݶ���
	if (PEM_read_bio_RSAPrivateKey(priBio, &m_privateKey, NULL, NULL) == NULL);
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(priBio);
	return true;
 
}
