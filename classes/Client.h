#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __CLIENT_H__
#define __CLIENT_H__
#include<iostream>  
#include<WinSock2.h>

#include"Information.h"
//#include <ctime>
//客户端  单例模式

#pragma comment(lib,"WS2_32.lib")  
using namespace std;

#define PORT 9999

class Client
{
private:
	WSADATA wsaData;
	SOCKET sHost;
	SOCKADDR_IN addrServer;
	static Client * client;
	explicit Client();
	bool init();
public:
	~Client()
	{
		closesocket(sHost);
		WSACleanup();
		delete client;
	}

	static int count;
	static Client* getInstance();

	BOOL ConnectServer();
	BOOL recv_Cli();
	BOOL send_Cli();

	void SendThread();		//建立子进程
	void RecvThread();

};
#endif