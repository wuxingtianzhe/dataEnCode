#pragma once
#include<map>
#include"TcpSocket.h"
#include"TcpServer.h"
#include"Request.h"
using namespace std;
/*
"serverID":"BJ-QianMen-001",
"dbUser":"xyz",
"dbPasswd":"123456",
"dbSID":"orcl",
"port":8989,
"maxnode":20,
"shmkey":"/home/bin"
*/
struct ServerInfo
{
	string serverID;
	string dbUser;
	string dbPasswd;
	string dbSID;
	unsigned short port;
	int maxNode;
	string shmKey;

};
enum Keylen
{
	LenSamll = 16,
	LenNormal = 24,
	LenLarge = 32
};
class serverOP
{
public:
	serverOP(string jsonfile);
	~serverOP();
	//操作函数
	//启动服务器
	void startServer();
	//密钥协商
	string seckeyAgree(RequestMsg* msg);
	 static void* working(void* arg);
private:
	string getRandStr(Keylen num);
private:
	TcpServer * m_server;
	ServerInfo m_info;
	map<pthread_t, TcpSocket*> m_socket;
};

