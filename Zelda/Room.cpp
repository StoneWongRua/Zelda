/*
*@Discription ∑øº‰¿‡    
*@Author tong
*@Date   2019/9/19
*/
#include "Room.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Room::Room()
{
	for (int i = 0; i < 4; ++i)
	{
		paths[i] = nullptr;
	}

	for (int i = 0; i < 5; ++i)
	{
		cur_items[i] = nullptr;
	}

	cur_monster = nullptr;
	cur_princess = nullptr;

	description = nullptr;
	room_num = 0;
}

Room::~Room()
{
	if (description)
	{
		delete[] description;
	}
}

int Room::DirectionIndex(char const* direction)
{
	int i = 0;

	if (strcmp(direction, "NORTH") == 0)
	{
		i = 0;
	}
	else if (strcmp(direction, "SOUTH") == 0)
	{
		i = 1;
	}
	else if (strcmp(direction, "EAST") == 0)
	{
		i = 2;
	}
	else if (strcmp(direction, "WEST") == 0)
	{
		i = 3;
	}

	return i;
}

char* Room::DirectionName(int i)
{
	char* buffer = new char[10];

	if (i == 0)
	{
		strcpy_s(buffer, 10, "North");
	}
	else if (i == 1)
	{
		strcpy_s(buffer, 10, "South");
	}
	else if (i == 2)
	{
		strcpy_s(buffer, 10, "East");
	}
	else if (i == 3)
	{
		strcpy_s(buffer, 10, "West");
	}

	return buffer;
}

bool Room::IsRoomFull()
{
	for (int i = 0; i < 5; ++i)
	{
		if (cur_items[i] == nullptr)
		{
			return false;
		}
	}

	return true;
}

Room** Room::GetPaths()
{
	return paths;
}

Item** Room::GetCurItems()
{
	return cur_items;
}

Monster* Room::GetCurMonster()
{
	return cur_monster;
}

Princess* Room::GetCurPrincess()
{
	return cur_princess;
}


char* Room::GetDescription()
{
	return description;
}

int Room::GetRoomNumber()
{
	return room_num;
}

// paths[0] = North
// paths[1] = South
// paths[2] = East
// paths[3] = West

void Room::SetNorth(Room* roomNo)
{
	paths[0] = roomNo;
}

void Room::SetSouth(Room* roomNo)
{
	paths[1] = roomNo;
}

void Room::SetEast(Room* roomNo)
{
	paths[2] = roomNo;
}

void Room::SetWest(Room* roomNo)
{
	paths[3] = roomNo;
}

void Room::SetCurItem(int item_num, Item* item)
{
	cur_items[item_num] = item;
}

void Room::SetCurMonster(Monster* monster)
{
	cur_monster = monster;
}

void Room::SetCurPrincess(Princess* princess)
{
	cur_princess = princess;
}

void Room::SetDiscription(char const* room_Description)
{
	description = new char[strlen(room_Description) + 1];
	strcpy_s(description, strlen(room_Description) + 1, room_Description);
}

void Room::SetRoomNumber(int roomNo)
{
	room_num = roomNo;
}
