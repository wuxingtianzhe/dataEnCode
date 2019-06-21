#pragma once
#include"codecFactory.h"
#include"Request.h"
#include"codec.h"
using namespace std;
class RequestFactory:public codecFactory
{
public:
	RequestFactory(string enc);
	RequestFactory(RequestInfo* info);
	codec* createCodec();
	~RequestFactory();
private:
	bool m_flag;
	string m_encStr;
	RequestInfo* m_info;

};