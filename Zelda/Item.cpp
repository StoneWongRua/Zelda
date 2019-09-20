/*
*@Discription 物品类头文件    
*@Author tong
*@Date   2019/9/19
*/

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