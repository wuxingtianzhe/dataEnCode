#pragma once
#include"codec.h"
using namespace std;
class codecFactory
{
public:
	codecFactory();
	virtual codec* createCodec();
	virtual ~codecFactory();

};