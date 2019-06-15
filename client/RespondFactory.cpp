#include "RespondFactory.h"

RespondFactory::RespondFactory(string enc)
{
	m_flag = false;
	m_encStr = enc;
}

RespondFactory::RespondFactory(RespondInfo * info)
{
	m_flag = true;
	m_info = info;
}

codec * RespondFactory::createCodec()
{
	codec* codec = NULL;
	if (m_flag)
	{
		codec = new Response(m_info);

	}
	else
	{
		codec = new Response(m_encStr);
	}
	return codec;
}

RespondFactory::~RespondFactory()
{
}
