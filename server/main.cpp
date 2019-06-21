#include <cstdio>
#include<iostream>
#include"serverOP.h"
using namespace std;

int main()
{
	serverOP op("server.json");
	op.startServer();
    return 0;
}