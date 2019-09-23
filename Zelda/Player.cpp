/*
*@Discription 玩家动作/状态  
*@Author tong
*@Date   2019/9/19
*/

#include "Player.h"
#include "Helper.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;

Player::Player(char const* player_Name, Room* room1)
{
	name = new char[strlen(player_Name) + 1];
	strcpy_s(name, strlen(player_Name) + 1, player_Name);

	cur_room = room1;
	princess_ptr = nullptr;
	is_alive = true;
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		bag[i] = nullptr;
	}
}

Player::Player()
{

}

Player::~Player()
{
	if (name)
	{
		delete[] name;
	}
}

bool Player::GetCurState()
{
	return is_alive;
}

void Player::SetCurState(bool currentState)
{
	is_alive = currentState;
}

Princess* Player::GetPrincessPtr()
{
	return princess_ptr;
}

char* Player::GetPlayerName()
{
	return name;
}

void Player::CashUpdater()
{
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (bag[i])
		{
			cash = cash + bag[i]->GetWorth();
		}
	}
}

int Player::GetCash()
{
	return cash;
}

bool Player::IsBagEmpty()
{
	for (int i = 0; i < 10; ++i)
	{
		if (bag[i] != nullptr)
			return false;
	}
	return true;
}

bool Player::IsBagFull()
{
	bool bag_full = true;

	for (int i = 0; i < 10 && bag_full; ++i)
	{
		if (bag[i] == nullptr)
		{
			bag_full = false;
		}
	}
	return bag_full;
}

bool Player::Move(char const* direction, bool& exit_Castle)
{
	bool moveSuccessful = false;
	int i = 0;

	i = cur_room->DirectionIndex(direction);

	if ((i == 3) && ((cur_room->GetRoomNumber()) == 1))
	{
		exit_Castle = true;
	}
	else if ((cur_room->GetPaths())[i] != nullptr)
	{
		cur_room = (cur_room->GetPaths())[i];
		moveSuccessful = true;

		if (cur_room->GetCurPrincess())
		{
			Helper::Color(AQUA);
			cout << "公主站在黑暗中等待着你。";
			princess_ptr = cur_room->GetCurPrincess();
			cur_room->SetCurPrincess(nullptr);
		}
		Helper ::Color(RED);
		cout << "\n您已成功转移到房间: " << cur_room->GetRoomNumber();
	}
	else
	{
		Helper::Color(RED);
		cout << "\nMOVE " << direction << "是无效命令.";
	}
	return moveSuccessful;
}


void Player::Pick(char const* itemName)
{
	bool picked = false;
	bool itemFound = false;
	for (int i = 0; i < 5; ++i)
	{
		if ((cur_room->GetCurItems())[i] != nullptr)
		{
			if (strcmp((((cur_room->GetCurItems())[i])->GetItemName()), itemName) == 0)
			{
				itemFound = true;

				if (!IsBagFull())
				{
					int j = 0;

					for (; bag[j] != nullptr; ++j)
					{

					}

					bag[j] = (cur_room->GetCurItems())[i];
					cur_room->SetCurItem(i, nullptr);

					picked = true;

					CashUpdater();
				}
				else
				{
					cout << "\n背包已满";
				}
			}
		}
	}

	Helper::Color(RED);
	if (picked)
	{
		cout << endl << itemName << "成功收集。";
	}

	else if (itemFound == false)
	{
		cout << endl << itemName << "不在当前房间。";
	}
}

void Player::Drop(char const* itemName)
{
	bool dropped = false;
	bool item_in_bag = false;

	for (int i = 0; i < 10; ++i)
	{
		if (bag[i] != NULL)
		{
			if (strcmp((bag[i])->GetItemName(), itemName) == 0)
			{
				item_in_bag = true;

				if (!(cur_room->IsRoomFull()))
				{
					int j = 0;

					for (; (cur_room->GetCurItems())[j] != nullptr; ++j)
					{

					}

					cur_room->SetCurItem(j, bag[i]);
					bag[i] = nullptr;

					dropped = true;

					CashUpdater();
				}
				else
				{
					Helper::Color(AQUA);
					cout << "/n/" << itemName << "不能在此房间被丢弃。 " << cur_room->GetRoomNumber()
						<< "房间已满。";
				}
			}
		}
	}

	Helper::Color(YELLOW);

	if (dropped)
	{
		cout << endl << itemName << "已经被丢弃。";

	}
	else if (item_in_bag == false)
	{
		cout << endl << itemName << "不能丢弃，因为它不在你的包里。";
	}
}

bool Player::Attack(char const* monsterName)
{
	bool killed = false;

	if (cur_room->GetCurMonster() != nullptr)
	{
		if (((cur_room->GetCurMonster())->GetLivingState()) == true)
		{
			for (int i = 0; i < 10; ++i)
			{
				if ((cur_room->GetCurMonster())->GetKillingWeapon() == bag[i])
				{
					(cur_room->GetCurMonster())->SetLivingState(false);
					Helper::Color(RED);
					cout << monsterName << "已经被杀死。 ";

					killed = true;
				}
			}
			if (killed == false)
			{
				SetCurState(false);
				Helper::Color(RED);
				cout << "\n你的背包中没有杀死" << monsterName << "所需的武器。\n";
				
			}
		}
		else if ((((cur_room->GetCurMonster())->GetLivingState()) == false))
		{
			cout << endl << monsterName << "已经死亡。";
		}
	}
	else
	{
		cout << endl << monsterName << "不在当前房间。";
	}

	return killed;
}

void Player::Look()
{
	Helper::Color(RED);
	cout << "\n你现在在房间" << cur_room->GetRoomNumber() << "。\n";

	for (int i = 0; i < 4; ++i)
	{
		Helper::Color(AQUA);

		if ((cur_room->GetPaths())[i] != NULL)
		{
			cout << "你的 " << cur_room->DirectionName(i) << "边有1间房间。\n";
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		Helper::Color(WHITE);
		if ((cur_room->GetCurItems())[i] != NULL)
		{
			cout << "房里有"<<((cur_room->GetCurItems())[i])->GetItemName();
		}
	}

	if (cur_room->GetCurMonster() != NULL)
	{
		Helper::Color(RED);
		if ((cur_room->GetCurMonster())->GetLivingState() == true)
		{
			cout << (cur_room->GetCurMonster())->GetMonsterName() << "正准备从你身后锁住的门后杀死你。\n";
		}
		else
		{
			cout << (cur_room->GetCurMonster())->GetMonsterName() << "躺在地上濒临死亡。";
		}
	}

	Helper::Color(PURPLE);
	if (princess_ptr)
	{
		cout << "公主跟你在一起。";
	}

	Helper::Color(GREEN);
	cout << "\n你的背包现在有如下物品: ";


	if (!IsBagEmpty())
	{
		for (int i = 0; i < 10; ++i)
		{
			if (bag[i])
			{
				cout << endl << bag[i]->GetItemName();
			}
		}
	}
	else
	{
		cout << "\n目前你的背包为空。";
	}

	Helper::Color(BLUE);
	cout << "\n当前余额：: " << GetCash();
}

void Player::Exit()
{
	Helper::Color(WHITE);
	cout << "感谢" << GetPlayerName() << "体验游戏。\n游戏退出中 .........";
}





