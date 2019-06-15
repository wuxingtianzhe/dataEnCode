#include "Response.h"

Response::Response()
{
}

Response::Response(string encstr)
{
	initMessage(encstr);
}

Response::Response(RespondInfo * info)
{
	initMessage(info);
}





void Response::initMessage(string encstr)
{
	m_encStr = encstr;
}

void Response::initMessage(RespondInfo * info)
{
	m_msg.set_rv(info->status);
	m_msg.set_seckeyid(info->seckeyID);
	m_msg.set_clientid(info->clientID);
	m_msg.set_serverid(info->serverID);
	m_msg.set_data(info->data);
}





string Response::encodeMsg()
{
	string output;
	m_msg.SerializeToString(&output);
	return output;
}

void * Response::decodeMsg()
{
	m_msg.ParseFromString(m_encStr);
	return &m_msg;
}

Response::~Response()
{
}
