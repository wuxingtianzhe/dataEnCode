#pragma once
#include"msg.pb.h"
#include"codec.h"
using namespace std;
struct RequestInfo
{
	int cmd;
	string clientID;
	string serverID;
	string sign;
	string data;
};
class Request :public codec
{
public:
	Request();
	Request(string encstr);
	Request(RequestInfo* info);
	//Request(int cmd, string clientID, string serverID, string sign, string data);
	void initMessage(string encstr);
	void initMessage(RequestInfo* info);
	//void initMessage(int cmd, string clientID, string serverID, string sign, string data);
	string encodeMsg();
	void* decodeMsg();
	~Request();

private:
	string m_encStr;
	RequestMsg m_msg;
};