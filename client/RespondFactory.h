#pragma once
#include"codec.h"
#include"Response.h"
#include"codecFactory.h"
using namespace std;
class RespondFactory :public codecFactory
{
public:
	RespondFactory(string enc);
	RespondFactory(RespondInfo* info);
	codec* createCodec();
	~RespondFactory();

private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};

