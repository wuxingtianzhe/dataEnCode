#include <cstdio>
 
int usage();
int main()
{
	
 
	while (1)
	{
		int sel = usage();
		switch (sel)
		{
		case 1:
			//密钥协商
			break;
		case 2:
			//密钥校验
			break;
		case 3:
			//密钥注销
			break;
		case 4:
			//密钥查看
			break;
		case 5:
			//退出系统
			break;
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