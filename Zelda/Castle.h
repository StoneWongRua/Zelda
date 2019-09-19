#pragma once
#include "Room.h"
class Castle
{
public:
	Castle();
	~Castle();

	Room*  GetRoom(int);

	void LinkRoomsWithOrtherThings(Item**, Monster**, Princess*);
	void HiddenRoomsUnlocker(char const*, Monster**);
	void LinkRoom5and8();
	void LinkRoom6and9();

	void SetDecriptionOfRooms();
	void SetNumbersofRooms();



private:
	Room rooms[9];
};