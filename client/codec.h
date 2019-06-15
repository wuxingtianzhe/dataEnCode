#pragma once
#include<string>
using namespace std;
class codec
{

	public:
		codec();
		virtual string encodeMsg();
		virtual void* decodeMsg();
		virtual ~codec();

};