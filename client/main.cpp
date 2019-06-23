#include <cstdio>
#include"ClientOP.h"
#include<iostream>
#include<unistd.h>

using namespace std;
int usage();
int main()
{
	ClientOP op("client.json");
 
	while (1)
	{
		int sel = usage();
		switch (sel)
		{
		case 1:
			//密钥协商
			op.seckeyAgree();
			cout << "您选择了密钥协商功能" << endl;
			break;
		case 2:
			//密钥校验
			op.seckeyCheck();
			cout << "您选择了密钥校验" << endl;
			break;
		case 3:
			//密钥注销
			op.seckeyWithdraw();
			cout << "您选择了密钥注销" << endl;
			break;
		case 4:
			//密钥查看
			cout << "您选择了密钥查看功能" << endl;
			break;
		case 5:
			//退出系统
			cout << "您已经退出系统" << endl;
			break;
		}
		if (sel==5)
		{
			sleep(5);
			return 0;
		}
	}
	
  //  printf("hello from client!\n",sel);
    return 0;
}
int usage()
{

	int nSel = -1;
	printf("\n  /*************************************************************/");
	printf("\n  /*************************************************************/");
	printf("\n  /*     1.密钥协商                                            */");
	printf("\n  /*     2.密钥校验                                            */");
	printf("\n  /*     3.密钥注销                                            */");
	printf("\n  /*     4.密钥查看                                            */");
	printf("\n  /*     0.退出系统                                            */");
	printf("\n  /*************************************************************/");
	printf("\n  /*************************************************************/");
	printf("\n\n  选择:");
	scanf("%d", &nSel);
	while (getchar() != '\n');
	return nSel;
}