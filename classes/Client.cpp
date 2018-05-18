#include "Client.h"
#include <thread>
#include <algorithm>
#include "cocos2d.h"

USING_NS_CC;

#define TIME_LAG 500		//发送和接收信息的时间间隔

extern Information information;

Client* Client::client = new Client();
int Client::count = 0;

bool Client::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))//成功返回0  
	{
		return FALSE;
	}

	SOCKET sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}

	//3 准备通信地址  
	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = inet_addr("192.168.0.3");
	
	return true;
}

BOOL Client::ConnectServer()
{
	if (SOCKET_ERROR == connect(sHost, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		//cout <<clock()-start;
		closesocket(sHost);
		WSACleanup();
		system("pause");
		return FALSE;
	}

	return TRUE;
}

BOOL Client::recv_Cli()
{
	char recvBuf[BUFLEN+1];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sHost, recvBuf, sizeof(recvBuf), 0))
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}
	recvBuf[BUFLEN] = '\0';
	information.setRecvBuf(recvBuf);

	return TRUE;
}

BOOL Client::send_Cli()
{
	if (SOCKET_ERROR == send(sHost, const_cast<char *>(information.getSendBuf().c_str()), information.getSendBuf().length(), 0))
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}
	information.clearSendBuf();
	return TRUE;
}


Client::Client()
{
	if (!init())
	{
		log("init Client false!");
	}

	if (!ConnectServer())
	{
		log("can't connect Server!");
	}
}

Client* Client::getInstance()
{
	if (count == 1)
	{
		thread SendThread(client->SendThread);
		thread RecvThread(client->RecvThread);
	}
	++count;
	return client;
}

void Client::SendThread()
{
	while (true)
	{
		send_Cli();
		Sleep(TIME_LAG);
	}
}

void Client::RecvThread()
{
	while (true)
	{
		recv_Cli();
		Sleep(TIME_LAG);
	}
}
