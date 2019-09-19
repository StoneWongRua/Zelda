#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#include "define.h"

using namespace std;

//��ȡ�ظ�����
void DoReadRspns(SOCKET fd, RsponsPacket *ptr)
{
	int count = 0;
	int  size = sizeof(RsponsPacket);
	while (count < size)
	{
		//int recv( _In_ SOCKET s, _Out_ char *buf, _In_ int len, _In_ int flags);
		//int recv(ָ�����ն��׽������������������recv���յ������ݵĻ�������ָ���������ĳ��ȣ�ָ�����÷�ʽ��һ��Ϊ0))
		int nRead = recv(fd, (char*)ptr + count, size - count, 0);
		if (nRead <= 0)
		{
			printf("read response error");
			closesocket(fd);
			exit(1);
		}
		count += nRead;
	}
}

//���������
void DoWriteCmd(SOCKET fd, CmdPacket *ptr)
{
	int size = sizeof(CmdPacket);
	int flag = send(fd, (char*)ptr, size, 0);

	if (flag == SOCKET_ERROR)
	{
		printf("write cmd error");
		closesocket(fd);
		WSACleanup(); //��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
		exit(1);
	}
}

//���������׽��ֲ��ҽ������״̬
SOCKET CreateDataSocket()
{
	SOCKET sockfd;
	struct sockaddr_in myAddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("socket error in create data socket");
		WSACleanup();
		exit(1);
	}

	//׼��ͨ�ŵ�ַ
	myAddr.sin_family = AF_INET; //sin_familyָ��Э���壬��socket�����ֻ����AF_INET
	myAddr.sin_port = htons(DATA_PORT); //htons ʹ�������ֽ�˳��
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(myAddr.sin_zero), 0, sizeof(myAddr.sin_zero));

	//��
	if (bind(sockfd, (struct sockaddr*)&myAddr, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		printf("bind error %d in create data socket!\n", err);
		closesocket(sockfd);
		WSACleanup();
		exit(1);
	}

	//������������
	if (listen(sockfd, 1) == SOCKET_ERROR)
	{
		printf("listen error in create data socket!");
		closesocket(sockfd);
		WSACleanup();
		exit(1);
	}

	return sockfd;
}

//����get����->����
void GetFile(SOCKET sockfd)
{
	FILE* fd;
	char data_buf[DATA_BUFSIZE];

	CmdPacket cmdPacket;
	RsponsPacket rsponsPacket;

	SOCKET newsockfd, data_sockfd;
	struct sockaddr_in their_addr;
	int sin_size;
	int count;

	//���������
	cmdPacket.cmdtype = GET;
	scanf("%s", cmdPacket.param);

	//�򿪻��ߴ��������ļ��Թ�д������
	fd = fopen(cmdPacket.param, "wb");
	if (fd == NULL)
	{
		printf("Open file %s for write failed!\n", cmdPacket.param);
		return;
	}

	//�����������Ӳ��ҿ��Լ�������������������
	newsockfd = CreateDataSocket();

	//���������
	DoWriteCmd(sockfd, &cmdPacket);

	//��ȡ�ظ�����
	DoReadRspns(sockfd, &rsponsPacket);

	if (rsponsPacket.rsponstype == ERRORS)
	{
		printf("%s", rsponsPacket.text);
		closesocket(newsockfd);
		fclose(fd);

		DeleteFile(cmdPacket.param);
		return;
	}

	sin_size = sizeof(struct sockaddr_in);

	//�ȴ����ܷ���������������
	if ((data_sockfd = accept(newsockfd, (struct sockaddr*)&their_addr, &sin_size)) == INVALID_SOCKET)
	{
		printf("accept error in getting file!\n");
		closesocket(newsockfd);

		fclose(fd);

		DeleteFile(cmdPacket.param);
		return;
	}

	// ѭ����ȡ�������ݲ�д���ļ���
	while ((count = recv(data_sockfd, data_buf, DATA_BUFSIZE, 0)) > 0)
	{
		fwrite(data_buf, sizeof(char), count, fd);
	}

	closesocket(data_sockfd);
	closesocket(newsockfd);
	fclose(fd);

}

//����put����->�ϴ�
void PutFile(SOCKET sockfd)
{
	FILE* fd;
	CmdPacket cmdPacket;
	RsponsPacket rsponsPacket;
	char data_buf[DATA_BUFSIZE];

	SOCKET newsockfd, data_sockfd;
	struct sockaddr_in their_addr;
	int sin_size;
	int count;

	cmdPacket.cmdtype = PUT;
	scanf("%s", cmdPacket.param);

	fd = fopen(cmdPacket.param, "rb");
	if (fd == NULL)
	{
		printf("open %s for reading failed!\n", cmdPacket.param);
		return;
	}

	newsockfd = CreateDataSocket();

	DoWriteCmd(sockfd, &cmdPacket);

	DoReadRspns(sockfd, &rsponsPacket);
	if (rsponsPacket.rsponstype == ERRORS)
	{
		printf("%s", rsponsPacket.text);
		closesocket(newsockfd);
		fclose(fd);
		return;
	}

	sin_size = sizeof(struct sockaddr_in);
	if ((data_sockfd = accept(newsockfd, (struct sockaddr*)&their_addr, &sin_size)) == INVALID_SOCKET)
	{
		printf("accept error in puting file!\n");
		closesocket(newsockfd);
		fclose(fd);
		return;
	}

	while (true)
	{
		count = fread(data_buf, sizeof(char), DATA_BUFSIZE, fd);
		send(data_sockfd, data_buf, count, 0);
		if (count < DATA_BUFSIZE)
		{
			break;
		}
	}
	closesocket(data_sockfd);
	closesocket(newsockfd);
	fclose(fd);
}


//�����˳����
void quit(int sockfd)
{
	CmdPacket cmd_packet;
	RsponsPacket rspns_packet;

	cmd_packet.cmdtype = QUIT;
	DoWriteCmd(sockfd, &cmd_packet);

	DoReadRspns(sockfd, &rspns_packet);
	printf("%s", rspns_packet.text);
}

void main()
{
	SOCKET sockfd;
	struct hostent* he;
	struct sockaddr_in their_addr;
	char cmd[10];
	RsponsPacket rsponsPacket;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	//Winsock��ʼ����
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("WinSock initialized failed!\n");
		return;
	}

	//ȷ��WinSock DLL�İ汾��2.2��
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("WinSock version is not 2.2!\n");
		WSACleanup();
		return;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == INVALID_SOCKET)
	{
		printf("error to ctreate socket!\n");
		WSACleanup();
		exit(1);
	}

	char host[100] = { 0 };
	if (gethostname(host, sizeof(host)) < 0)
	{
		printf("gethostbyname failed!");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(CMD_PORT);
	their_addr.sin_addr = *(struct in_addr *)gethostbyname(host)->h_addr_list[0];
	memset(&(their_addr.sin_zero), 0, sizeof(their_addr.sin_zero));

	// ���ӷ�������
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		printf("connect error");
		closesocket(sockfd);
		WSACleanup();
		exit(1);
	}

	//���ӳɹ������Ƚ��շ��������ص���Ϣ��
	DoReadRspns(sockfd, &rsponsPacket);
	printf("%s", rsponsPacket.text);

	while (true)
	{
		scanf("%s", cmd);
		switch (cmd[0])
		{
		case 'g':
			GetFile(sockfd);
		case 'p':
			PutFile(sockfd);
		default:
			break;
		}
	}
	WSACleanup();
}



