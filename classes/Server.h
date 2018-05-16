#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __SERVER_H__
#define __SERVER_H__

//服务器		由服务器主机运行
#include "WinSock2.h"	//socket 所需文件
#pragma comment(lib,"WS2_32.lib")	// link socket 库
#include <iostream>
#include <vector>

#include "Information.h"

#define PORT 9999
#define BUFLEN 1024
#define MAXCLIENTS 8
//不使用构造和析构函数
using namespace std;

class Server
{
private:
	WSADATA wsaData;
	SOCKET sServer;
	SOCKADDR_IN addrServer;
	sockaddr_in addrClient;
	SOCKET sClient;
	Information information;
	//int num_Clients;

public:
	bool init();
	~Server();

	BOOL AcceptClients();
	BOOL recv_Ser();
	BOOL send_Ser();
};

#endif