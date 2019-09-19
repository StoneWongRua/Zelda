#pragma once
class Weapon :public Item
{
private:
public:
	Weapon();
	~Weapon();

	Weapon(char const*);
	inline int GetWorth();
};