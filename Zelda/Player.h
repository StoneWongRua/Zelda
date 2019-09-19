#pragma once
#include "Princess.h"
#include "Item.h"
#include "Room.h"
class Player
{
private:
	char* name;
	Princess* princess_ptr;
	Item* bag[10];
	Room* cur_room;

	bool is_alive;
	int cash;

	bool IsBagEmpty();
	bool IsBagFull();

public:
	Player();
	~Player();

	Player(const char*, Room*);

	bool GetCurState();
	void SetCurState(bool);

	Princess* GetPrincessPtr();

	void CashUpdater();
	int GetCash();
	char* GetPlayerName();

	bool Move(char const*, bool&);
	void Pick(char const*);
	void Drop(char const*);
	void Look();
	bool Attack(char const*);
	void Exit();

};