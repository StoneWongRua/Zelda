/*
*@Discription 命令大小写转换以及字体颜色    
*@Author tong
*@Date   2019/9/20
*/
#include "Helper.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;


void Helper::CharactersCase(char* input)
{
	for (int i = 0; input[i] != '\0'; ++i)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] = input[i] - 32;
		}
	}
}

void Helper::Color(int k)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}