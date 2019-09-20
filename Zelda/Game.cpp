/*
*@Discription ÓÎÏ·Ö÷Âß¼­    
*@Author tong
*@Date   2019/9/20
*/

#include "Game.h"
#include "Helper.h"
#include "Socket.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;

Game::Game()
{
	items_ptr[0] = new Treasure("GOLDEN EGG", 500000);
	items_ptr[1] = new Treasure("GOLDEN CHALICE", 500000);
	items_ptr[2] = new Treasure("PROOF", 1000000);
	items_ptr[3] = new Weapon("SHIELD");
	items_ptr[4] = new Weapon("DAGGER");

	monsters_ptr[0] = new Monster("MEDUSA", items_ptr[3]);
	monsters_ptr[1] = new Monster("DRACULA", items_ptr[4]);

	princess_ptr = new Princess;

	castle_ptr = new Castle;

	castle_ptr->LinkRoomsWithOrtherThings(items_ptr, monsters_ptr, princess_ptr);
	castle_ptr->SetDecriptionOfRooms();
	castle_ptr->SetNumbersofRooms();

	char username[20];
	Helper::Color(YELLOW);
	std::cout << "Enter your name : ";
	std::cin.getline(username, 20);

	player_ptr = new Player(username, castle_ptr->GetRoom(1));
}

Game::~Game()
{
	for (int i = 0; i < 5; ++i)
	{
		delete items_ptr[i];
	}

	for (int i = 0; i < 2; ++i)
	{
		delete monsters_ptr[i];
	}

	delete princess_ptr;

	delete castle_ptr;

	delete player_ptr;
}

void Game::DisplayStory()
{
	char file_name[FILE_NAME_MAX_SIZE + 1] = "start.txt";
	SocketHst socketHst;
	socketHst.Download(file_name);
	ifstream InputStream(file_name);

	if (InputStream.is_open())
	{
		Helper::Color(PURPLE);
		char buffer[200];

		while (!InputStream.eof())
		{
			InputStream.getline(buffer, 200);
			std::cout << buffer << std::endl;
		}
	}
	else
	{
		std::cout << "Could not open file";
	}
	InputStream.close();
	WSACleanup();
}

void Game::GameRule()
{
	char file_name[FILE_NAME_MAX_SIZE + 1] = "impl.txt";
	SocketHst socketHst;
	socketHst.Download(file_name);
	ifstream InputStream(file_name);

	if (InputStream.is_open())
	{
		//Helper::Color(w);
		char buffer[200];

		while (!InputStream.eof())
		{

			InputStream.getline(buffer, 200);
			std::cout << buffer << std::endl;
		}
	}
	else
	{
		std::cout << "Could not open file";
	}
	InputStream.close();
	WSACleanup();
}

void Game::PlayerDead()
{
	char file_name[FILE_NAME_MAX_SIZE + 1] = "enddead.txt";
	SocketHst socketHst;
	socketHst.Download(file_name);
	ifstream InputStream(file_name);

	if (InputStream.is_open())
	{
		Helper::Color(RED);

		while (!InputStream.eof())
		{
			char buffer[200];

			while (!InputStream.eof())
			{
				InputStream.getline(buffer, 200);
				std::cout << buffer << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Could not open file";
	}

	InputStream.close();
	WSACleanup();
}

void Game::GameCheck()
{
	if (player_ptr->GetPrincessPtr())
	{
		char file_name[FILE_NAME_MAX_SIZE + 1] = "endwin.txt";
		SocketHst socketHst;
		socketHst.Download(file_name);
		ifstream InputStream(file_name);

		if (InputStream.is_open())
		{
			Helper::Color(AQUA);

			char buffer[200];

			while (!InputStream.eof())
			{
				InputStream.getline(buffer, 200);
				cout << buffer << endl;
			}
		}
		else
		{
			cout << "Could not open file";
		}
		InputStream.close();
		WSACleanup();
	}
	else
	{
		char file_name[FILE_NAME_MAX_SIZE + 1] = "endlose.txt";
		SocketHst socketHst;
		socketHst.Download(file_name);
		ifstream InputStream(file_name);

		if (InputStream.is_open())
		{
			char buffer[200];
			Helper::Color(RED);
			while (!InputStream.eof())
			{
				InputStream.getline(buffer, 200);
				cout << buffer << endl;
			}
		}
		else
		{
			cout << "Could not open file";
		}
		InputStream.close();
	}
	WSACleanup();
}

void Game::Play()
{
	cout << "\n\n\n\n";
	char s[300] = "\t\t\t#####################################################\n"
		"\t\t\t#                                                   #\n"
		"\t\t\t#                     zelda                         #\n"
		"\t\t\t#                                                   #\n"
		"\t\t\t#####################################################";

	Helper::Color(RED);
	cout << s;
	cout << "\n\n";
	DisplayStory();
	cout << "\n\n";
	GameRule();

	char functionName[30];
	bool exit_Castle = false;
	player_ptr->Look();

	do
	{
		Helper::Color(YELLOW);
		cout << "\n\nWhat do you want to do : ";

		char fullCommand[30];
		cin.getline(fullCommand, 30);

		Helper::CharactersCase(fullCommand);

		char command[15];

		int i = 0;

		for (i = 0; fullCommand[i] != '\0' && fullCommand[i] != ' '; ++i)
		{
			functionName[i] = fullCommand[i];
		}

		functionName[i] = '\0';

		if (strlen(functionName) != strlen(fullCommand))
		{
			strcpy_s(command, 25, fullCommand + i + 1);
		}

		if (strcmp(functionName, "MOVE") == 0)
		{
			if (player_ptr->Move(command, exit_Castle))
			{
				player_ptr->Look();
			}
			if (exit_Castle == true)
			{
				GameCheck();
			}
		}
		else if (strcmp(functionName, "PICK") == 0)
		{
			player_ptr->Pick(command);
		}
		else if (strcmp(functionName, "DROP") == 0)
		{
			player_ptr->Drop(command);
		}
		else if (strcmp(functionName, "LOOK") == 0)
		{
			player_ptr->Look();
		}
		else if (strcmp(functionName, "ATTACK") == 0)
		{
			if (player_ptr->Attack(command))
			{
				castle_ptr->HiddenRoomsUnlocker(command, monsters_ptr);
			}
			else if (player_ptr->GetCurState() == false)
			{
				PlayerDead();
			}
		}
		else if (strcmp(functionName, "EXIT") == 0)
		{
			player_ptr->Exit();
		}
		else
		{
			Helper::Color(RED);
			cout << "\nINVALID COMMAND . Please enter a Valid Command .";
		}
	} while (player_ptr->GetCurState() && !exit_Castle && (strcmp(functionName, "EXIT") != 0));
}
