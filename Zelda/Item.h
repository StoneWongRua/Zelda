/*
*@Discription 物品类头文件    
*@Author tong
*@Date   2019/9/20
*/
#pragma once

class Item
{
public:
	Item();
	~Item();

	char* GetItemName();
	virtual int GetWorth() = 0;

protected:
	char* name;

};

class Treasure :public Item
{
public:
	Treasure();
	~Treasure();
	Treasure(char const*, int);
	int GetWorth();

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
	int GetWorth();
};