/*
*@Discription Œ‰∆˜¿‡    
*@Author tong
*@Date   2019/9/20
*/

#include "Item.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

Weapon::Weapon(char const* weapon_name)
{
	name = new char[strlen(weapon_name) + 1];
	strcpy_s(name, strlen(weapon_name) + 1, weapon_name);
}

int Weapon::GetWorth()
{
	return 0;
}