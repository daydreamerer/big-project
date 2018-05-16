#include "Server.h"


bool Server::init()		//如果init返回False，用return退出程序
{
	//num_Clients = 0;
	// 启动并初始化winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}
	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}

	//设置套接字非阻塞模式 
	unsigned long ul = 1;
	if (SOCKET_ERROR == ioctlsocket(sServer, FIONBIO, (unsigned long*)&ul))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	// 准备通信地址
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = INADDR_ANY; //本机任意可用网络地址

	if (SOCKET_ERROR == ::bind(sServer, (const sockaddr*)&addrServer, sizeof(SOCKADDR_IN)))		//使用::bind避免命名冲突
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	//listen
	if (SOCKET_ERROR == listen(sServer, SOMAXCONN))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	//等待客户端连接
	return TRUE;
}

BOOL Server::AcceptClients()
{
	sockaddr_in addrClient;
	int addrClientLen = sizeof(addrClient);

	sClient = accept(sServer, (sockaddr *)&addrClient, &addrClientLen);
	if (INVALID_SOCKET == sClient)
	{
		cout << WSAGetLastError() << endl;
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}
	//++num_Clients;
	return TRUE;
}

BOOL Server::recv_Ser()
{
	char* recvBuf = const_cast<char*>(information.getRecvBuf().c_str());
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sClient, recvBuf, sizeof(recvBuf), 0))
	{
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}

	information.setSendAndRecv(recvBuf);
	return TRUE;
}

//发送数据
BOOL Server::send_Ser()
{
	char* sendBuf = const_cast<char*>(information.getSendBuf().c_str());
	if (SOCKET_ERROR == send(sClient, sendBuf, sizeof(sendBuf), 0))
	{
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

Server::~Server()
{
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
}