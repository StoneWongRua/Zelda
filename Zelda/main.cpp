/*
*@Discription 程序运行入口    
*@Author tong
*@Date   2019/9/20
*/
#include "Game.h"
#include <windows.h>
int main()
{
	Game* game = new Game();
	game->Play();

	system("PAUSE");

	return 0;
}



