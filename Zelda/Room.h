/*
*@Discription 房间类头文件    
*@Author tong
*@Date   2019/9/20
*/
#pragma once

#include "Item.h"
#include "Monster.h"
#include "Princess.h"

class Room
{
private:
	Room* paths[4];
	Item* cur_items[5];
	Monster* cur_monster;
	Princess* cur_princess;

	char* description;
	int room_num;

public:
	Room();
	~Room();

	Room** GetPaths();
	Item** GetCurItems();
	Monster* GetCurMonster();
	Princess* GetCurPrincess();
	char* GetDescription();
	int GetRoomNumber();

	bool IsRoomFull();

	int DirectionIndex(char const*);
	char* DirectionName(int);

	void SetEast(Room*);
	void SetWest(Room*);
	void SetSouth(Room*);
	void SetNorth(Room*);

	void SetCurMonster(Monster*);
	void SetCurItem(int, Item*);
	void SetCurPrincess(Princess*);
	void SetDiscription(char const*);
	void SetRoomNumber(int);
};
