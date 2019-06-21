#include "serverOP.h"
#include"Cryptographic.h"
#include"TcpServer.h"
#include"TcpSocket.h"
#include"RequestFactory.h"
#include"RespondFactory.h"
#include"codec.h"
#include<fstream>
#include<json/json.h>
#include<unistd.h>
#include"Hash.h"
//#include<json/reader.h>
using namespace Json;
serverOP::serverOP(string jsonfile)
{
	//加载配置文件
	//1.读磁盘的Json文件
	ifstream ifs(jsonfile);
	//2.创建流对象
	Reader rd;
	Value root;
	//3.使用Cjson Reader->value
	rd.parse(ifs, root);
	//4.value->m_info
	m_info.serverID = root["serverID"].asString();
	m_info.dbUser = root["dbUser"].asString();
	m_info.dbPasswd = root["dbPasswd"].asString();
	m_info.dbSID = root["dbSID"].asString();
	m_info.maxNode = root["maxnode"].asInt();
	m_info.port = root["port"].asInt();
	m_info.shmKey = root["shmkey"].asString();
	cout <<"serverID:"<< root["serverID"].asString() << endl;
	cout << "port:"<< root["port"].asInt() << endl;
	ifs.close();
}

serverOP::~serverOP()
{
	delete m_server;
}

void serverOP::startServer()
{
	//创建tcpserver对象
	cout << "start server" << endl;
	m_server = new TcpServer();
	//设置监听
	m_server->setListen(m_info.port);
	//接受 连接请求
	while (true)
	{
	TcpSocket* pSocket= m_server->acceptConn();
	if (pSocket==NULL)
	{
		cout << "accept error..." << endl;
		continue;
	}
	cout << "accept success" << endl;
	//通信
	pthread_t tid;
	cout << "创建了一个客户端线程" << endl;
	pthread_create(&tid, NULL, working, this);
	pthread_detach(tid);
	//通信的套接字放到容器中
	m_socket.insert(make_pair(tid, pSocket));
	cout << "加入了套接字" << endl;
	}

}

string serverOP::seckeyAgree(RequestMsg * msg)
{
	
	//2.将得到的公钥写入服务器磁盘
	//写入的文件名，由于客户端有很多连接服务器，需要对写入的公钥进行区分
	//文件名：clientID+".pem"
	cout << "接收的公钥的文件内容：" << endl;
	cout << msg->data() << endl;
	cout << "clientid" << msg->clientid();
	string filename = msg->clientid() + ".pem";
	cout << "生成文件名.pem" << endl;
	ofstream ofs(filename);
	ofs << msg->data();
	ofs.close();
	cout << "磁盘上生成了公钥文件..." << endl;
	//1.校验签名
	Cryptographic rsa(filename,false);
	Hash hash(T_SHA1);
	hash.addData(msg->data());
	bool bl=rsa.rsaVerify(hash.result(),msg->sign());
	//2.准备给客户端回复的 协商数据
	RespondInfo info;
	if (bl==false)
	{
		cout << "签名校验失败...." << endl;

		info.status = false;
		
	}
	else
	{
		info.status = true;
		cout << "签名验证成功" << endl;
		//3.生成一个随机字符串 --对称加密的密钥
		string seckey = getRandStr(LenNormal);
		//4.回复数据-》结构体
		//5.数据初始化-》密钥使用的公钥加密
		info.clientID = msg->clientid();
		info.serverID = m_info.serverID;
		info.seckeyID = 124;
		//对称加密的密钥用公钥加密
		cout << "对称加密密钥：" << seckey << endl;
		info.data = rsa.rsaPubKeyEncrypt(seckey);
		/*string private_s=rsa.rsaPriKeyDecrypt(info.data);
		cout << "解密后的密钥：" << private_s << endl;*/
	}

	
	//6.通过工厂函数创建编码对象-》编码
	codecFactory* factory = new RespondFactory(&info);
	codec*  code=factory->createCodec();
	string sendMsg=code->encodeMsg();

	//7.要回复给客户端的数据得到了
	delete factory;
	delete code;
	return sendMsg;
}

void * serverOP::working(void * arg)
{
	//sleep一会，让主线程先把信息添加进去
	usleep(100);
	//得到通信的套接字
	serverOP* op = (serverOP*)arg;
	TcpSocket* psocket=op->m_socket[pthread_self()];
	//接受数据-》编码之后的
	string revMsg=psocket->recvMsg();
	cout << "接收到的客户端原始数据：" << endl;
	cout << revMsg << endl;
	//对接收的数据解码
	codecFactory* factory = new RequestFactory(revMsg);
	codec* code=factory->createCodec();
	RequestMsg* reqMsg=(RequestMsg*)code->decodeMsg();

	/*delete factory;
	delete code;*/
	//注释：为啥这里释放内存会导致bug
	//
	//根据cmd判断客户的请求
	string str;
	
	////密钥协商
	//cout << "123214124124:" << reqMsg->cmdtype() << endl;
	//cout << "12333333333333333333333" << reqMsg->clientid() << endl;

	//str = op->seckeyAgree(reqMsg);
	switch (reqMsg->cmdtype())
	{
	case 1:
		//密钥协商
		cout << "123214124124:" << reqMsg->cmdtype() << endl;
		cout << "12333333333333333333333" << reqMsg->clientid() << endl;
		str = op->seckeyAgree(reqMsg);
		break;
	 
	}
	psocket->sendMsg(str);
	psocket->disConnect();
	delete  factory;
	delete code;
	return nullptr;
}

//随机字符串中有
//0-9，a-z,A-Z,特殊字符
string serverOP::getRandStr(Keylen num)
{
	char* bufStr = "!@#$%^&*()_+<>?;:~";
	string retStr = string();
	for (int i = 0; i < num; i++)
	{
		switch (rand()%4)
		{
		case 0:
			//0-9
			retStr.append(1, rand() % 10 + '0');
			break;
		case 1:
			//a-z
			retStr.append(1, rand() % 26 + 'a');
			break;
		case 2:
			//A-Z
			retStr.append(1, rand() % 26 + 'A');
			break;
		case 3:
			retStr.append(1, bufStr[rand()%strlen(bufStr)]);
			break;
		}

	}
	return retStr;
}
