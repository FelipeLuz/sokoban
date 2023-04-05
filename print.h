#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "conmanip.h"
#include "models.h"
#include "constants.h"

using namespace conmanip;
using namespace std;

void printCenter(string output)
{
    console_out_context ctxout;
    console_out conout(ctxout);
    int middle = conout.getsize().X/2;
    cout << setposx(middle - output.length()/ 2) << output;
    ctxout.restore(console_cleanup_options::restore_attibutes);
}

void printAt(int x, int y, string val, console_text_colors textColor, console_bg_colors bgColor)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    console_out_context ctxout;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << settextcolor(textColor) << setbgcolor(bgColor) << val;
    ctxout.restore(console_cleanup_options::restore_attibutes);
}

template<typename T1>
void printAtMultiline(int x, int y, T1 val[], int lineCount, console_text_colors textColor, console_bg_colors bgColor )
{
    for (int i = 0; i < lineCount; i++)
    {
        printAt(x, y + i, val[i], textColor, bgColor);
    }
}

void printPlayer(COORD &coord, player player)
{
    printAtMultiline(player.x*6, player.y*2, PLAYER, 2, console_text_colors::light_yellow, console_bg_colors::black);
}

void printBoxes(COORD &coord, box boxes[], int boxCount)
{
    for(int i = 0; i < boxCount; i++)
    {
        printAtMultiline(boxes[i].x*6, boxes[i].y*2, BOX, 2, (console_text_colors) (i + 2), (console_bg_colors) (i + 2));
    }
}

void printHoles(COORD &coord, hole holes[], int holeCount)
{
    for(int i = 0; i < holeCount; i++)
    {
        printAtMultiline(holes[i].x *6 + 1, holes[i].y*2, HOLE,1, console_text_colors::red, console_bg_colors::black);
    }
}

void printMap(COORD &coord, int map[10][10])
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for(int i=0;i<10;i++)
    {
        string line = "";
        for(int j=0;j<10;j++)
        {
            switch (map[i][j])
            {
                case 0: 
                    line += SPACE + SPACE + SPACE + SPACE + SPACE + SPACE;
                    break;
                case 1: 
                    line +=  WALL + WALL + WALL + WALL +  WALL + WALL ;
                    break;
            }
        }

        cout << line << '\n' << line;
        cout<<"\n";
    }
}