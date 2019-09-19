#pragma once
#include "Item.h"
class Monster
{
public:
	Monster();
	~Monster();

	Monster(char const*, Item*);
	Item* GetKillingWeapon();
	void SetKillingWeapon(Item*);
	bool GetLivingState();
	void SetLivingState(bool);
	char* GetMonsterName();

private:
	char* monster_name;
	bool is_alive;
	Item* killing_weapon;

};