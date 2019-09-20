/*
*@Discription 总地图布局    
*@Author tong
*@Date   2019/9/19
*/

#include "Castle.h"
#include "Socket.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

Castle::Castle()
{

}

Room* Castle::GetRoom(int room_No)
{
	return &rooms[room_No - 1];
}

void Castle::LinkRoomsWithOrtherThings(Item** items, Monster** monsters, Princess* princess)
{
	//Room1
	rooms[0].SetSouth(&rooms[3]);
	rooms[0].SetEast(&rooms[1]);
	//room1.west = Exit from castle


	//Room2
	rooms[1].SetWest(&rooms[0]);
	rooms[1].SetEast(&rooms[2]);
	rooms[1].SetSouth(&rooms[4]);

	rooms[1].SetCurItem(0, items[0]);


	//Room3
	rooms[2].SetWest(&rooms[1]);
	rooms[2].SetCurItem(0, items[3]);


	//Room4
	rooms[3].SetNorth(&rooms[0]);
	rooms[3].SetCurItem(0, items[1]);


	//Room5
	rooms[4].SetNorth(&rooms[1]);
	rooms[4].SetEast(&rooms[5]);

	rooms[4].SetCurMonster(monsters[0]);


	//Room6
	rooms[5].SetWest(&rooms[4]);

	rooms[5].SetCurMonster(monsters[1]);


	//Room7
	rooms[6].SetEast(&rooms[7]);
	rooms[6].SetCurItem(0, items[4]);


	//Room8
	rooms[7].SetWest(&rooms[6]);
	rooms[7].SetNorth(&rooms[4]);

	rooms[7].SetCurItem(0, items[2]);


	//Room9
	rooms[8].SetNorth(&rooms[5]);
	rooms[8].SetCurPrincess(princess);
}

void Castle::LinkRoom5and8()
{
	rooms[4].SetSouth(&rooms[7]);
	rooms[7].SetNorth(&rooms[4]);
}

void Castle::LinkRoom6and9()
{
	rooms[5].SetSouth(&rooms[8]);
	rooms[8].SetNorth(&rooms[5]);
}

void Castle::HiddenRoomsUnlocker(char const* monstername, Monster** monsters)
{
	if (strcmp(monstername, (monsters[0]->GetMonsterName())) == 0)
	{
		LinkRoom5and8();
	}

	else if (strcmp(monstername, (monsters[1]->GetMonsterName())) == 0)
	{
		LinkRoom6and9();
	}
}

void Castle::SetDecriptionOfRooms()
{
	char file_name[FILE_NAME_MAX_SIZE + 1] = "rooms.txt";
	SocketHst socketHst;
	socketHst.Download(file_name);
	ifstream InputStream(file_name);
	if (InputStream.is_open())
	{
		char buffer[300];
		for (int i = 0; i < 9 && !InputStream.eof(); ++i)
		{
			InputStream.getline(buffer, 300);
			rooms[i].SetDiscription(buffer);
		}
	}
	else
	{
		cout << "Could not open file";
	}
	InputStream.close();
}

void Castle::SetNumbersofRooms()
{
	for (int i = 0; i < 9; ++i)
	{
		rooms[i].SetRoomNumber(i + 1);
	}
}

Castle::~Castle()
{

}
