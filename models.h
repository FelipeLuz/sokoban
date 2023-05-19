#include <stdio.h>
#include <iostream>
using namespace std;


struct box {
    int x;
    int y;
};

struct player {
    int x;
    int y;
};

struct hole {
    int x;
    int y;
};

struct assets
{
    hole holes[5];
    box boxes[5];
    player player;

    int map[10][10];
    int boxCount;
    int moveCount;
    string playerName;
    string mapName;

    void init()
    {
        boxCount = 0;
        moveCount = 0;
        boxes[0] = {.x = 0, .y = 0};
        boxes[1] = {.x = 0, .y = 0};
        boxes[2] = {.x = 0, .y = 0};
        boxes[3] = {.x = 0, .y = 0};
        boxes[4] = {.x = 0, .y = 0};

        holes[0] = {.x = 0, .y = 0};
        holes[1] = {.x = 0, .y = 0};
        holes[2] = {.x = 0, .y = 0};
        holes[3] = {.x = 0, .y = 0};
        holes[4] = {.x = 0, .y = 0};
    }
};

struct history
{
    assets assets[10];
};