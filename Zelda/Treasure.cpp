#include "Item.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Treasure::Treasure()
{
	worth = 0;
}

Treasure::~Treasure()
{

}

Treasure::Treasure(char const* treasure_name, int treasure_worth)
{
	name = new char[strlen(treasure_name) + 1];
	strcpy_s(name, strlen(treasure_name) + 1, treasure_name);

	worth = treasure_worth;
}

int Treasure::GetWorth()
{
	return worth;
}