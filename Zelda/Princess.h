/*
*@Discription ������ͷ�ļ�    
*@Author tong
*@Date   2019/9/20
*/
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