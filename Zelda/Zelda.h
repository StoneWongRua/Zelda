#pragma once

/*Some COLOR Constants*/
const int RED = 12;
const int PURPLE = 13;
const int GREEN = 10;
const int AQUA = 11;
const int YELLOW = 14;
const int WHITE = 15;
const int BLUE = 9;

//classes
class Helper;
class Item;
class Treasure;
class Weapon;
class Monster;
class Princess;
class Player;
class Room;
class Castle;
class Game;

//Definitions
class Helper
{
public:
	inline Helper();
	~Helper();
	static void CharactersCase(char*);
	static void Color(int);

private:

};

class Item
{
public:
	Item();
	~Item();

	inline char* GetItemName();
	inline virtual int GetWorth() = 0;

protected:
	char* name;

};

class Treasure :public Item
{
public:
	Treasure();
	~Treasure();
	Treasure(char const*, int);
	inline int GetWorth();

private:
	int worth;
};

class Weapon :public Item
{
private:
public:
	Weapon();
	~Weapon();

	Weapon(char const*);
	inline int GetWorth();
};

class Monster
{
public:
	Monster();
	~Monster();
	
	Monster(char const*, Item*);
	inline Item* GetKillingWeapon();
	inline void SetKillingWeapon(Item*);
	inline bool GetLivingState();
	inline void SetLivingState(bool);
	inline char* GetMonsterName();

private:
	char* monster_name;
	bool is_alive;
	Item* killing_weapon;

};

class Princess
{
public:
	Princess();
	~Princess();

	inline bool GetLivingState();
	inline void SetLivingState(bool);

private:
	bool is_alive;

};

class Room
{
private:
	Room* paths[4];
	Item* cur_items[5];
	Monster* cur_monster;
	Princess* cur_princess;

	char* description;
	int room_num;

public:
	Room();
	~Room();

	inline Room** GetPaths();
	inline Item** GetCurItems();
	inline Monster* GetCurMonster();
	inline Princess* GetCurPrincess();
	inline char* GetDescription();
	inline int GetRoomNumber();

	bool IsRoomFull();

	int DirectionIndex(char const*); 
	char* DirectionName(int);

	inline void SetEast(Room*);
	inline void SetWest(Room*);
	inline void SetSouth(Room*);
	inline void SetNorth(Room*);

	inline void SetCurMonster(Monster*);
	inline void SetCurItem(int, Item*);
	inline void SetCurPrincess(Princess*);
	inline void SetDiscription(char const*);
	inline void SetRoomNumber(int);



};

class Castle
{
public:
	Castle();
	~Castle();

	inline Room*  GetRoom(int);

	void LinkRoomsWithOrtherThings(Item**, Monster**, Princess*);
	void HiddenRoomsUnlocker(char const*, Monster**);
	void LinkRoom5and8();
	void LinkRoom6and9();

	inline void SetDecriptionOfRooms();
	inline void SetNumbersofRooms();



private:
	Room rooms[9];
};

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

	inline bool GetCurState();
	inline void SetCurState(bool);

	inline Princess* GetPrincessPtr();

	void CashUpdater();
	inline int GetCash();
	inline char* GetPlayerName();
	
	bool Move(char const*, bool&);
	void Pick(char const*);
	void Drop(char const*);
	void Look();
	bool Attack(char const*);
	void Exit();

};

class Game
{
public:
	Game();
	~Game();
	void	 Play();
	void	 DisplayStory();
	void	 PlayerDead();
	void	 GameCheck();

private:
	Castle* 	castle_ptr;
	Item*		items_ptr[5];
	Princess*	princess_ptr;
	Monster* 	monsters_ptr[2];
	Player*		player_ptr;

};
