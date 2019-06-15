#include "Request.h"
#include<iostream>
Request::Request()
{
}

Request::Request(string encstr)
{
	initMessage(encstr);
}

Request::Request(RequestInfo * info)
{
	initMessage(info);
}



void Request::initMessage(string encstr)
{
	m_encStr = encstr;
}

void Request::initMessage(RequestInfo * info)
{
	m_msg.set_cmdtype(info->cmd);
	m_msg.set_clientid(info->clientID);
	m_msg.set_severid(info->serverID);
	m_msg.set_sign(info->sign);
	m_msg.set_data(info->data);
}


string Request::encodeMsg()
{
//	cout << "1" << endl;
	string output;
	m_msg.SerializeToString(&output);
//	cout << "2" << endl;
	return output;
}

void * Request::decodeMsg()
{
	m_msg.ParseFromString(m_encStr);
	return &m_msg;
}

Request::~Request()
{
}
