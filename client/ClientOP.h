#pragma once
#include<string>	
using namespace std;

struct ClientInfo
{
	string serverID;
	string clientID;
	string serverIP;
	int port;
	int maxNode;
	string shmKey;
};
class ClientOP
{
public:
	//��ʼ�����ݣ��Ӵ��̵������ļ���
	ClientOP(string filename);
	~ClientOP();
	//1.��ԿЭ��
	bool seckeyAgree();
	//2.��ԿУ��
	void seckeyCheck();
	//3.��Կע��
	void seckeyWithdraw();

private:
	ClientInfo m_info;
};

