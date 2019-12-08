// Pacman1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct ghostLocation {
	int x;
	int y;
};

const int MAX_FOOD = 10;
const char FOOD_CHAR = '.';
const char PACMAN_CHAR = 'C';
const char GHOST_CHAR = '9';
const int GENERATE_FOOD_EVERY_SECOND = 10;
const int SCORE_PER_FOOD = 5;
const int GHOST_RESPAWN_TIME = 20;

int currentSpawnedFood = 0;

void printMap();
void spawnFood();
ghostLocation spawnGhost();
void moveGhost(int &x, int &y);

//Default map
char map[25][25] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

int main()
{
	int x, y;
	int waitTenSecondCounter = 0;
	int waitGhostRespawnCounter = 0;
	int Score = 0;
	int counterGhostSpawned = 0;
	ghostLocation ghostsLocationsArray[100];
	ghostLocation newGhost;

	x = 10; y = 10;

	// Infinite Loop to run the game
	while (1)
	{
		system("CLS");

		if (GetAsyncKeyState(VK_UP))
		{
			if (map[y - 1][x] != '#' && map[y - 1][x] != FOOD_CHAR)
			{
				map[y][x] = ' ';
				y--;
			}
			else if (map[y - 1][x] == FOOD_CHAR)
			{
				map[y][x] = ' ';
				y--;

				currentSpawnedFood--;
				Score += SCORE_PER_FOOD;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (map[y + 1][x] != '#' && map[y + 1][x] != FOOD_CHAR)
			{
				map[y][x] = ' ';
				y++;
			}
			else if (map[y + 1][x] == FOOD_CHAR)
			{
				map[y][x] = ' ';
				y++;

				currentSpawnedFood--;
				Score += SCORE_PER_FOOD;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			if (map[y][x-1] != '#' && map[y][x-1] != FOOD_CHAR)
			{
				map[y][x] = ' ';
				x--;
			}
			else if (map[y][x - 1] == FOOD_CHAR)
			{
				map[y][x] = ' ';
				x--;

				currentSpawnedFood--;
				Score += SCORE_PER_FOOD;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (map[y][x+1] != '#' && map[y][x+1] != FOOD_CHAR)
			{
				map[y][x] = ' ';
				x++;
			}
			else if (map[y][x + 1] == FOOD_CHAR)
			{
				map[y][x] = ' ';
				x++;

				currentSpawnedFood--;
				Score += SCORE_PER_FOOD;
			}
		}

		map[y][x] = PACMAN_CHAR;

		waitTenSecondCounter++;
		if (waitTenSecondCounter == GENERATE_FOOD_EVERY_SECOND)
		{
			waitTenSecondCounter = 0;
			spawnFood();
		}

		waitGhostRespawnCounter++;
		if (waitGhostRespawnCounter == GHOST_RESPAWN_TIME * 5)
		{
			waitGhostRespawnCounter = 0;
			ghostsLocationsArray[counterGhostSpawned] = spawnGhost();
			counterGhostSpawned++;
		}

		cout << "Score: " << Score << endl;
	
		for (int i = 0; i < counterGhostSpawned; i++)
		{
			moveGhost(ghostsLocationsArray[i].x, ghostsLocationsArray[i].y);
		}
		

		printMap();

		//Pauses the game for 100 Millisec
		Sleep(100);
	}

	
}

void printMap()
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void spawnFood()
{
	int x, y;
	bool isCorrectLocation = false;

	srand(time(0));

	if (currentSpawnedFood >= 10)
		return;

	while (!isCorrectLocation)
	{
		x = rand() % 25;
		y = rand() % 25;

		if (map[y][x] != '#' && map[y][x] != PACMAN_CHAR)
		{
			isCorrectLocation = true;
			currentSpawnedFood++;
		}
			
	}

	//Spawn Food at x,y
	map[y][x] = FOOD_CHAR;
}

ghostLocation spawnGhost()
{
	int x, y;
	bool isCorrectLocation = false;
	ghostLocation temp;

	srand(time(0));

	while (!isCorrectLocation)
	{
		x = rand() % 25;
		y = rand() % 25;

		if (map[y][x] != '#' && map[y][x] != PACMAN_CHAR)
		{
			isCorrectLocation = true;
		}

	}
	//spawning our ghost at x,y
	map[y][x] = GHOST_CHAR;

	temp.x = x;
	temp.y = y;

	return temp;
}

void moveGhost(int &x, int &y)
{
	bool isCorrectLocation = false;

	srand(time(0));

	while (!isCorrectLocation)
	{
		int direction = rand() % 4 + 1;

		if (direction == 1)
		{
			if (map[y - 1][x] != '#')
			{
				//MOVE UP
				map[y][x] = ' ';
				y--;
				isCorrectLocation = true;
			}
		}
		else if (direction == 2)
		{
			if (map[y + 1][x] != '#')
			{
				//MOVE DOWN
				map[y][x] = ' ';
				y++;
				isCorrectLocation = true;
			}
		}
		else if (direction == 3)
		{
			if (map[y][x + 1] != '#')
			{
				//MOVE Right
				map[y][x] = ' ';
				x++;
				isCorrectLocation = true;
			}
		}
		else if (direction == 4)
		{
			if (map[y][x - 1] != '#')
			{
				//MOVE Left
				map[y][x] = ' ';
				x--;
				isCorrectLocation = true;
			}
		}
	}

	map[y][x] = GHOST_CHAR;
}
