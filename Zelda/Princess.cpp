#include "Princess.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

Princess::Princess()
{
	is_alive = true;
}

Princess::~Princess()
{

}

bool Princess::GetLivingState()
{
	return is_alive;
}

void Princess::SetLivingState(bool currentState)
{
	is_alive = currentState;
}