#include "ClientOP.h"
#include"codec.h"
#include"Request.h"
#include"Cryptographic.h"
#include<fstream>
#include<sstream>
#include"codec.h"
#include"codecFactory.h"
#include"RequestFactory.h"
#include"RespondFactory.h"
#include"TcpSocket.h"
#include<json/json.h>
#include<json/value.h>
#include<string>
#include"Hash.h"
using namespace Json;
#define DEBUG



ClientOP::ClientOP(string filename)
{

	// 1. 读磁盘的Json文件
	// 1.1 创建流对象 -> 读文件 ifstream
	ifstream ifs("client.json");
	// 1.2 使用CJson Reader -> Value
	Reader rd;
	Value root;
	rd.parse(ifs, root);

	//cout << 1 << endl;
	m_info.clientID = root["clientID"].asString();
	m_info.serverID = root["serverID"].asString();
	//cout << 2 << endl;
	m_info.serverIP = root["serverIP"].asString();
	m_info.port = root["serverPort"].asInt();
	m_info.maxNode = root["maxNode"].asInt();
	m_info.shmKey = root["shmKey"].asString();
	cout << m_info.clientID << endl;
	cout << m_info.port << endl;
}

ClientOP::~ClientOP()
{
}
/*
准备: 对称加密的秘钥, 通过非对称性加密的方式完成秘钥交换
数据发送:   通过protobuf序列化之后的结构体 -> A
数据的接收:	通过protobuf序列化之后的结构体 -> B
*/
bool ClientOP::seckeyAgree()
{
	//1.准备数据 ，并序列化
	 //1.1将磁盘中的配置文件赋值给序列号的结构体
	RequestInfo reqInfo;
	reqInfo.clientID = m_info.clientID;
	reqInfo.serverID = m_info.serverID;
	reqInfo.cmd = 1;
	
	//1.2生成rsa密钥对
	Cryptographic crypto;
	crypto.generateKeyFile(1024);
	 //1.3将磁盘中的公钥文件内容读出来
	ifstream ifs("public.pem");

	 // 通过文件流 -> 字符串流
	stringstream strBuf;
	strBuf << ifs.rdbuf();
	Hash hash(T_SHA1);
	hash.addData(strBuf.str());
	string sh1=	hash.result();
	//对公钥进行签名,表示数据的所有者，防止别人对数据进行修改
	reqInfo.sign = crypto.rsaSign(sh1);
	cout << "签名成功" << endl;

#ifdef DEBUG
	cout << "公钥信息：" << endl;
	cout << strBuf.str() << endl;
#endif // DEBUG

	 // 获取给服务器发送的数据 -> rsa 公钥
	reqInfo.data = strBuf.str();
	//序列化初始化的数据
	codecFactory* factory = new RequestFactory(&reqInfo);
	codec * code=factory->createCodec();
	string encodeMsg=code->encodeMsg();
#ifdef DEBUG
	cout << "数据编码完成..." << endl;
#endif // DEBUG

	//2.将编码之后的数据发送
	//创建一个客户端
	TcpSocket* socket = new TcpSocket();
	//请求链接
	socket->connectToHost(m_info.serverIP, m_info.port);
	//发送数据
	socket->sendMsg(encodeMsg);
	//等待并接收服务器数据
	string recvMsg=socket->recvMsg();
	//3.解密服务器回复的数据
	factory = new RespondFactory(recvMsg);
	code = factory->createCodec();
	RespondMsg* resMsg=(RespondMsg*)code->decodeMsg();
	//4判断状态
	bool ret = true;
	if (!resMsg->rv())
	{
		cout << "服务器请求失败..." << endl;
		ret = false;
	}
	else
	{
	//5.通过私钥将data解析出来
#ifdef DEBUG
		cout << "11111111111111111111111111111111111111111111111" << endl;
#endif // DEBUG

	string aeskey=crypto.rsaPriKeyDecrypt(resMsg->data());
	//crypto.rsaPriKeyDecrypt(resMsg->data());
	cout << "对称加密的密钥：" << aeskey << endl;
	//6.将aeskey存储到共享内存中

	}
	//7.是否释放资源
	delete factory;
	delete code;
	//8.关闭套接字
	socket->disConnect();
	delete socket;
	return ret;
}

void ClientOP::seckeyCheck()
{

}

void ClientOP::seckeyWithdraw()
{

}
