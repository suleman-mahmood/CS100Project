// Pacman1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Struction used to strore the value of the ghost's location coordinates
struct ghostLocation {
	int x;
	int y;
};

const int MAX_FOOD = 100;
const char FOOD_CHAR = '.';
const char PACMAN_CHAR = 'C';
const char GHOST_CHAR = '9';
const double GENERATE_FOOD_EVERY_SECOND = 0.5; // Value is in seconds
const int SCORE_PER_FOOD = 5;
const int GHOST_RESPAWN_TIME = 5; // Value is in seconds

// Prints the Array "map" on the screen
void printMap(); 

// Spawns Food at a random location in the map
void spawnFood(int& currentSpawnedFood);

// Spawns Ghost at a random location in map and returns its (x,y) coordinates of spawned location
ghostLocation spawnGhost();

// Moves the Ghost on the map
void moveGhost(int& x, int& y, bool& gameOver);

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
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

int main()
{
	int x, y; //The location of our character (pacman)
	int waitTenSecondCounter = 0; //counter to spawn food
	int waitGhostRespawnCounter = 0; // counter to spawn ghost
	int Score = 0; // Holds the runtime score of the player
	double totalTime = 0; //total time elapsed during the program runtime
	int counterGhostSpawned = 0; // Holds the number of ghosts currently spawned
	int currentSpawnedFood = 0; // Holds the number of currently spawned food

	bool gameOver = false; // Checks whether the character has died or game is over

	ghostLocation ghostsLocationsArray[100]; //Stores the location

	//Default location of our spawn point of character (pacman)
	x = 10; y = 10;

	// Infinite Loop to run the game
	while (1)
	{
		// Clears the screen
		system("CLS");
		// Calculates the total time elapsed
		totalTime += 0.1;

		// When Up Arrow Key is pressed
		if (GetAsyncKeyState(VK_UP))
		{
			//Checks whether the new location is free space
			if (map[y - 1][x] == ' ')
			{
				map[y][x] = ' ';
				y--;
			}
			//Checks whether we are moving to the food location
			else if (map[y - 1][x] == FOOD_CHAR)
			{
				map[y][x] = ' ';
				y--;

				currentSpawnedFood--;
				Score += SCORE_PER_FOOD;
			}
			//checks whether we are moving to the ghost location
			else if (map[y - 1][x] == GHOST_CHAR)
				gameOver = true;
		}
		// When Down Arrow Key is pressed
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (map[y + 1][x] == ' ')
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
			else if (map[y - 1][x] == GHOST_CHAR)
				gameOver = true;
		}
		// When Left Arrow Key is pressed
		else if (GetAsyncKeyState(VK_LEFT))
		{
			if (map[y][x-1] == ' ')
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
			else if (map[y - 1][x] == GHOST_CHAR)
				gameOver = true;
		}
		// When Right Arrow Key is pressed
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (map[y][x+1] == ' ')
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
			else if (map[y - 1][x] == GHOST_CHAR)
				gameOver = true;
		}

		// Move the pacman to the new location or the same location
		map[y][x] = PACMAN_CHAR;

		// Generates food every Second on random location
		waitTenSecondCounter++;
		if (waitTenSecondCounter == GENERATE_FOOD_EVERY_SECOND * 10)
		{
			waitTenSecondCounter = 0;
			spawnFood(currentSpawnedFood);
		}

		//Spawns Ghost every second at a random location
		waitGhostRespawnCounter++;
		if (waitGhostRespawnCounter == GHOST_RESPAWN_TIME * 10)
		{
			waitGhostRespawnCounter = 0;
			ghostsLocationsArray[counterGhostSpawned] = spawnGhost();
			counterGhostSpawned++;
		}

		// Displays runtime score
		cout << "Score: " << Score << endl;
	
		//Move all Ghosts
		for (int i = 0; i < counterGhostSpawned; i++)
		{
			moveGhost(ghostsLocationsArray[i].x, ghostsLocationsArray[i].y, gameOver);
		}
		
		if (gameOver)
			break;

		printMap();

		//Pauses the game for 100 Millisecond
		Sleep(100);
	}

	//Game Overed, Display Score
	system("CLS");
	cout << "Your Total Score was: " << Score << endl;
	cout << "You managed to survive for " << totalTime << " seconds..!" << endl;

	string dummy;
	cin >> dummy;
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

void spawnFood(int& currentSpawnedFood)
{
	int x, y;
	bool isCorrectLocation = false;

	srand(time(0));

	//Only spawns a fixed number of maximum foods
	if (currentSpawnedFood >= MAX_FOOD)
		return;

	//Finds correct location where there is empty space
	while (!isCorrectLocation)
	{
		x = rand() % 25;
		y = rand() % 25;

		if (map[y][x] != '#' && map[y][x] != PACMAN_CHAR && map[y][x] != FOOD_CHAR && map[y][x] != GHOST_CHAR)
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

	//Finds correct location where there is empty space
	while (!isCorrectLocation)
	{
		x = rand() % 25;
		y = rand() % 25;

		if (map[y][x] != '#' && map[y][x] != PACMAN_CHAR && map[y][x] != FOOD_CHAR && map[y][x] != GHOST_CHAR)
		{
			isCorrectLocation = true;
		}

	}
	//spawning our ghost at x,y
	map[y][x] = GHOST_CHAR;

	temp.x = x;
	temp.y = y;

	//returning the location where the ghost is spawned
	return temp;
}

// Moves the ghost in a valid direction in any random four directions (up/down/left/right)
void moveGhost(int &x, int &y, bool& gameOver)
{
	bool isCorrectLocation = false;

	srand(time(0));

	while (!isCorrectLocation)
	{
		// generates a random number between 1 and 4
		int direction = rand() % 4 + 1;

		// 1 indicates up direction
		if (direction == 1)
		{
			if (map[y - 1][x] != '#' && map[y - 1][x] != GHOST_CHAR)
			{
				//MOVE UP
				map[y][x] = ' ';
				y--;
				isCorrectLocation = true;
			}

		}
		// 2 indicates down direction
		else if (direction == 2)
		{
			if (map[y + 1][x] != '#' && map[y + 1][x] != GHOST_CHAR)
			{
				//MOVE DOWN
				map[y][x] = ' ';
				y++;
				isCorrectLocation = true;
			}
		}
		// 3 indicates right direction
		else if (direction == 3)
		{
			if (map[y][x + 1] != '#' && map[y][x + 1] != GHOST_CHAR)
			{
				//MOVE Right
				map[y][x] = ' ';
				x++;
				isCorrectLocation = true;
			}
		}
		// 4 indicates left direction
		else if (direction == 4)
		{
			if (map[y][x - 1] != '#' && map[y][x - 1] != GHOST_CHAR)
			{
				//MOVE Left
				map[y][x] = ' ';
				x--;
				isCorrectLocation = true;
			}
		}
	}

	if (map[y][x] == PACMAN_CHAR)
		gameOver = true;
		
	map[y][x] = GHOST_CHAR;
}
