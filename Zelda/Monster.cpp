/*
*@Discription π÷ŒÔ¿‡    
*@Author tong
*@Date   2019/9/20
*/
#include "Monster.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Monster::Monster()
{
	monster_name = nullptr;
	is_alive = true;
	killing_weapon = nullptr;
}

Monster::~Monster()
{
	if (monster_name)
	{
		delete[] monster_name;
	}
}

Monster::Monster(char const* monster_Name, Item* weapon)
{
	monster_name = new char [strlen(monster_Name) + 1];
	strcpy_s (monster_name,strlen (monster_Name) + 1, monster_Name);

	is_alive = true;
	killing_weapon = weapon;
}

Item* Monster::GetKillingWeapon()
{
	return killing_weapon;
}

void Monster::SetKillingWeapon(Item* item)
{
	killing_weapon = item;
}

bool Monster::GetLivingState()
{
	return is_alive;
}

void Monster::SetLivingState(bool currentState)
{
	is_alive = currentState;
}

char* Monster::GetMonsterName()
{
	return monster_name;
}