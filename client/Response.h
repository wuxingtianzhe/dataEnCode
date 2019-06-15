#pragma once
#include"msg.pb.h"
#include"codec.h"
using namespace std;
struct RespondInfo
{
	int status;
	int seckeyID;
	string clientID;
	string serverID;
	string data;
};
class Response :public codec
{
public:
	Response();
	Response(string encstr);
	Response(RespondInfo* info);

	//Response(int status, int sesckeyId,string clientID, string serverID, string data);
	void initMessage(string encstr);
	void initMessage(RespondInfo* info);
	//void initMessage(int status, int sesckeyId, string clientID, string serverID, string data);
	string encodeMsg();
	void* decodeMsg();
	~Response();

private:
	string m_encStr;
	RespondMsg m_msg;
};