#include "Socket.h"

SOCKET SocketHst::StarUpSocket()
{
	//初始化 socket dll
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 0);
	assert(WSAStartup(socketVersion, &wsaData) == 0);

	//创建socket
	SOCKET c_socket = socket(AF_INET, SOCK_STREAM, 0);
	assert(SOCKET_ERROR != c_socket);

	//指定服务端的地址
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(PORT);
	assert(SOCKET_ERROR != connect(c_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)));
	return c_socket;
}

void SocketHst::Download(char file_name[])
{

		//初始化 Client 端 套接字
		SOCKET c_socket = StarUpSocket();

		//输入文件名
		//char file_name[FILE_NAME_MAX_SIZE + 1];
		//memset(file_name, 0, FILE_NAME_MAX_SIZE + 1);
		//std::cout << "Input File Name On Server ：" << std::endl;
		//std::cin >> file_name;

		//const char file_name[FILE_NAME_MAX_SIZE + 1] = "test.txt";
		

		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));  //取较短的

		//向服务器发送文件名
		assert(send(c_socket, buffer, BUFFER_SIZE, 0) >= 0);

		//打开文件，准备写入
		FILE *fp = fopen(file_name, "wb");  //以只写，二进制的方式打开一个文件
		assert(NULL != fp);
		memset(buffer, 0, BUFFER_SIZE);
		int length = 0;
		while ((length = recv(c_socket, buffer, BUFFER_SIZE, 0)) > 0)
		{
			assert(fwrite(buffer, sizeof(char), length, fp) >= (size_t)length);
			memset(buffer, 0, BUFFER_SIZE);
		}
//		std::cout << "Receive File : " << file_name << " From Server Successful !" << std::endl;
		fclose(fp);
		closesocket(c_socket);

		//释放winsock 库	
		WSACleanup();
	


}

//int main()
//{
//	char file_name[FILE_NAME_MAX_SIZE + 1] = "rooms.txt";
//	SocketHst socketHst;
//	socketHst.Download(file_name);
//}