#include "menu.h"
#include<fstream>

bool checkComplete(box boxes[], hole holes[], int boxCount)
{
    int completedCount = 0;

    for(int i = 0; i < boxCount; i++)
    {
        for(int j = 0; j < boxCount; j++)
        {
            if( boxes[i].x == holes[j].x && boxes[i].y == holes[j].y)
                completedCount++;
        }
    }

    return completedCount == boxCount;
}

bool checkBoxMove(int map[10][10], box boxes[], int boxCount, box box)
{
    for(int i = 0; i < boxCount; i++)
    {
        if( boxes[i].x == box.x && boxes[i].y == box.y )
        {
            return false;
        }
    }

    return !map[box.y][box.x];
}

bool checkBoxCollision(int map[10][10], player player, box boxes[], int boxCount, int xMove, int yMove)
{
    for(int i = 0; i < boxCount; i++)
    {
        if( boxes[i].x == player.x && boxes[i].y == player.y )
        {
            box tempBox = {.x = boxes[i].x + xMove, .y = boxes[i].y + yMove};
            if( checkBoxMove(map, boxes, boxCount, tempBox) )
            {
                boxes[i] = tempBox;
                return true;
            }
            return false;
        }
    }

    return true;
}

bool checkPlayerMove(int map[10][10], player player)
{
    return !map[player.y][player.x];
}

void saveMove(char move) 
{
    ofstream file("moves.csv", ios_base::app);

    if (file.is_open())
    {
        file << move << ',';
    }

    file.close();
}

player move(char input, player lastPos, box boxes[], int boxSize,int map[10][10], int &moveCount)
{
    player newPos = lastPos;
    switch(input)
    {
        case 72: case 'w': ///cima
            newPos.y--;
        break;
        case 80: case 's': ///baixo
            newPos.y++;
        break;
        case 75:case 'a': ///esquerda
            newPos.x--;
        break;
        case 77: case 'd': ///direita
            newPos.x++;
        break;
    }
    int xMove = newPos.x - lastPos.x;
    int yMove = newPos.y - lastPos.y;
    
    bool canMove = checkPlayerMove(map, newPos) && checkBoxCollision(map, newPos, boxes, boxSize, xMove, yMove);
    
    if(canMove)
    {
        moveCount++;
        saveMove(input);
        return newPos;
    }

    return lastPos;
}
