#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 24;
const int height = 24;
const int spawnx = 12;
const int spawny = 12;
const char pacman = '9';

char map[width][height];

void printMap();
void initialiseMap();

int main()
{
    int x,y;

    x = spawnx;
    y = spawny;

    initialiseMap();

    while(1)
    {
        Sleep(100);

        printMap();

        if(GetAsyncKeyState(VK_UP))
        {
            if(map[y][x] != '#')
            {
                map[y][x] = ' ';
                y--;
            }
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            if(map[y][x] != '#')
            {
                map[y][x] = ' ';
                y++;
            }
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            if(map[y][x] != '#')
            {
                map[y][x] = ' ';
                x--;
            }
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            if(map[y][x] != '#')
            {
                map[y][x] = ' ';
                x++;
            }
        }
        map[y][x] = pacman;
    }

    return 0;
}

void printMap()
{
    system("CLS");
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}

void initialiseMap()
{
    for(int i = 0; i < width; i++)
    {
        map[0][i] = '#';
    }
    for(int i = 1; i < height - 1; i++)
    {
        map[i][0] = '#';

        for(int j = 1; j < width - 1; j++)
        {
            map[i][j] = ' ';
        }

        map[i][width-1] = '#';
    }
    for(int i = 0; i < width; i++)
    {
        map[height - 1][i] = '#';
    }

    map[spawny][spawnx] = pacman;
}
