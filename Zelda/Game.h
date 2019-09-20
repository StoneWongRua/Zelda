/*
*@Discription 游戏类头文件    
*@Author tong
*@Date   2019/9/20
*/

#pragma once
#include "Castle.h"
#include "Item.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	void Play();
	void DisplayStory();
	void PlayerDead();
	void GameCheck();
	void GameRule();

private:
	Castle* castle_ptr;
	Item* items_ptr[5];
	Princess* princess_ptr;
	Monster* monsters_ptr[2];
	Player* player_ptr;

};