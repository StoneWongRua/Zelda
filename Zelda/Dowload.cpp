/*
*@brief  从服务端下载资源文件  
*@Author tong
*@Date   2019/9/19   
*/

#include "Socket.h"
SOCKET SocketHst::StarUpSocket()
{	
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 0);
	assert(WSAStartup(socketVersion, &wsaData) == 0);

	
	SOCKET c_socket = socket(AF_INET, SOCK_STREAM, 0);
	assert(SOCKET_ERROR != c_socket);

	
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(PORT);
	assert(SOCKET_ERROR != connect(c_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)));
	return c_socket;
}

void SocketHst::Download(char file_name[])
{		
	SOCKET c_socket = StarUpSocket();
		
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));  //取较短的

	assert(send(c_socket, buffer, BUFFER_SIZE, 0) >= 0);

	FILE *fp = fopen(file_name, "wb"); 
	assert(NULL != fp);
	memset(buffer, 0, BUFFER_SIZE);
	int length = 0;
	while ((length = recv(c_socket, buffer, BUFFER_SIZE, 0)) > 0)
	{
		assert(fwrite(buffer, sizeof(char), length, fp) >= (size_t)length);
		memset(buffer, 0, BUFFER_SIZE);
	}

	fclose(fp);
	closesocket(c_socket);

	WSACleanup();
}