#pragma once

class Princess
{
public:
	Princess();
	~Princess();

	bool GetLivingState();
	void SetLivingState(bool);

private:
	bool is_alive;

};