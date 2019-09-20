/*
*@Discription socket‘§∂®“Â    
*@Author tong
*@Date   2019/9/20
*/
#pragma once
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <WinSock2.h>

#define PORT_R 8088
#define PORT_S 8087
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
#pragma comment(lib, "WS2_32")

class SocketHst
{
public:
	SOCKET StarUpSocket(int PORT);
	void Download(char file_name[]);
protected:

private:

};