#include "RequestFactory.h"
#include"codec.h"
using namespace std;
RequestFactory::RequestFactory(string enc):codecFactory()
{
	m_flag = false;
	m_encStr = enc;
}



RequestFactory::RequestFactory(RequestInfo * info) :codecFactory()
{
	m_flag = true;
	m_info = info;
}

codec * RequestFactory::createCodec()
{
	codec* codec = NULL;
	//cout << "reuqet" << codec << endl;
	if (m_flag)
	{
		codec = new Request(m_info);
	}
	else
	{
		codec = new Request(m_encStr);
	}
	

	return codec;
}

RequestFactory::~RequestFactory()
{
}
