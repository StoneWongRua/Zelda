#include "Item.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Item::Item()
{
	name = nullptr;
}

Item::~Item()
{
	if (name)
	{
		delete[] name;
	}
}

char* Item::GetItemName()
{
	return name;
}