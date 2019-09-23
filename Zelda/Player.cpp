/*
*@Discription ��Ҷ���/״̬  
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
			cout << "����վ�ںڰ��еȴ����㡣";
			princess_ptr = cur_room->GetCurPrincess();
			cur_room->SetCurPrincess(nullptr);
		}
		Helper ::Color(RED);
		cout << "\n���ѳɹ�ת�Ƶ�����: " << cur_room->GetRoomNumber();
	}
	else
	{
		Helper::Color(RED);
		cout << "\nMOVE " << direction << "����Ч����.";
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
					cout << "\n��������";
				}
			}
		}
	}

	Helper::Color(RED);
	if (picked)
	{
		cout << endl << itemName << "�ɹ��ռ���";
	}

	else if (itemFound == false)
	{
		cout << endl << itemName << "���ڵ�ǰ���䡣";
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
					cout << "/n/" << itemName << "�����ڴ˷��䱻������ " << cur_room->GetRoomNumber()
						<< "����������";
				}
			}
		}
	}

	Helper::Color(YELLOW);

	if (dropped)
	{
		cout << endl << itemName << "�Ѿ���������";

	}
	else if (item_in_bag == false)
	{
		cout << endl << itemName << "���ܶ�������Ϊ��������İ��";
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
					cout << monsterName << "�Ѿ���ɱ���� ";

					killed = true;
				}
			}
			if (killed == false)
			{
				SetCurState(false);
				Helper::Color(RED);
				cout << "\n��ı�����û��ɱ��" << monsterName << "�����������\n";
				
			}
		}
		else if ((((cur_room->GetCurMonster())->GetLivingState()) == false))
		{
			cout << endl << monsterName << "�Ѿ�������";
		}
	}
	else
	{
		cout << endl << monsterName << "���ڵ�ǰ���䡣";
	}

	return killed;
}

void Player::Look()
{
	Helper::Color(RED);
	cout << "\n�������ڷ���" << cur_room->GetRoomNumber() << "��\n";

	for (int i = 0; i < 4; ++i)
	{
		Helper::Color(AQUA);

		if ((cur_room->GetPaths())[i] != NULL)
		{
			cout << "��� " << cur_room->DirectionName(i) << "����1�䷿�䡣\n";
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		Helper::Color(WHITE);
		if ((cur_room->GetCurItems())[i] != NULL)
		{
			cout << "������"<<((cur_room->GetCurItems())[i])->GetItemName();
		}
	}

	if (cur_room->GetCurMonster() != NULL)
	{
		Helper::Color(RED);
		if ((cur_room->GetCurMonster())->GetLivingState() == true)
		{
			cout << (cur_room->GetCurMonster())->GetMonsterName() << "��׼�����������ס���ź�ɱ���㡣\n";
		}
		else
		{
			cout << (cur_room->GetCurMonster())->GetMonsterName() << "���ڵ��ϱ���������";
		}
	}

	Helper::Color(PURPLE);
	if (princess_ptr)
	{
		cout << "����������һ��";
	}

	Helper::Color(GREEN);
	cout << "\n��ı���������������Ʒ: ";


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
		cout << "\nĿǰ��ı���Ϊ�ա�";
	}

	Helper::Color(BLUE);
	cout << "\n��ǰ��: " << GetCash();
}

void Player::Exit()
{
	Helper::Color(WHITE);
	cout << "��л" << GetPlayerName() << "������Ϸ��\n��Ϸ�˳��� .........";
}





