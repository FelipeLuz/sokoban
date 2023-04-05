/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
    versão final: Felipe Luz
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include "conmanip.h"
#include "gameHelper.h"

using namespace conmanip;
using namespace std;

void finishMenu(COORD &coord);
void pauseMenu(COORD &coord);
void startMenu(COORD &coord);

void setFontSize(int a, int b) 
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();

    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);

    lpConsoleCurrentFontEx->dwFontSize.X = a;
    lpConsoleCurrentFontEx->dwFontSize.Y = b;
    lpConsoleCurrentFontEx->FontWeight = 1000;

    SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}

void setup(COORD &coord)
{
    
///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    setFontSize(25, 25);

    console_out_context ctxout;
    console_out conout(ctxout);
    conout.settitle("Sokoban - Felipe Luz");
    //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    short int CX=0, CY=0;
    
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.
}

void game(COORD &coord, int map[10][10], player player, box boxes[], hole holes[], int boxCount)
{
    printMap(coord, map);
    printHoles(coord, holes, boxCount);
    printPlayer(coord, player);
    printBoxes(coord, boxes, boxCount);
    
    if(checkComplete(boxes, holes, boxCount))
    {
        finishMenu(coord);
        return;
    }

    char input = getInput();
    
    if(input == 27) 
        pauseMenu(coord);

    player = move(input, player, boxes, boxCount, map);

    game(coord, map, player, boxes, holes, boxCount);
}

void map0(COORD &coord)
{
    int map[10][10] = { 0,1,1,1,1,1,0,0,0,0,
                        0,1,0,0,0,1,1,1,1,0,
                        0,1,0,0,0,1,0,0,1,0,
                        0,1,1,0,0,0,0,0,1,0,
                        1,1,1,0,1,1,1,0,1,0,
                        1,0,0,0,1,0,1,0,1,0,
                        1,0,0,0,1,0,1,1,1,0,
                        1,0,0,0,1,0,0,0,0,0,
                        1,1,1,1,1,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,};
    hole holes[3];
    holes[0] = {.x = 7, .y = 3};
    holes[1] = {.x = 7, .y = 4};
    holes[2] = {.x = 7, .y = 5};

    box boxes[3];
    boxes[0] = {.x = 2, .y = 6};
    boxes[1] = {.x = 2, .y = 5};
    boxes[2] = {.x = 3, .y = 6};

    player player = {.x = 1, .y = 7};
    clear();
    game(coord, map, player, boxes, holes, 3);
}

void map1(COORD &coord)
{
    int map[10][10] = { 0,0,1,1,1,1,1,1,1,0,
                        0,0,1,0,0,0,0,0,1,0,
                        0,0,1,0,0,0,0,0,1,0,
                        1,1,1,1,1,0,1,0,1,0,
                        1,0,0,0,0,0,0,0,1,0,
                        1,0,0,1,0,1,1,0,1,1,
                        1,0,0,0,0,0,1,0,0,1,
                        1,0,0,0,0,0,0,0,0,1,
                        1,1,1,1,1,1,1,1,1,1,
                        0,0,0,0,0,0,0,0,0,0,};
    hole holes[4];
    holes[0] = {.x = 1, .y = 6};
    holes[1] = {.x = 1, .y = 7};
    holes[2] = {.x = 2, .y = 6};
    holes[3] = {.x = 2, .y = 7};

    box boxes[4];
    boxes[0] = {.x = 2, .y = 4};
    boxes[1] = {.x = 3, .y = 6};
    boxes[2] = {.x = 4, .y = 5};
    boxes[3] = {.x = 4, .y = 2};

    player player = {.x = 6, .y = 2};
    clear();
    game(coord, map, player, boxes, holes, 4);
}

void map2(COORD &coord)
{
    int map[10][10] = { 1,1,1,1,1,1,0,0,0,0,
                        1,0,0,0,0,1,0,0,0,0,
                        1,0,0,0,0,1,0,0,0,0,
                        1,1,0,0,0,1,0,0,0,0,
                        1,1,0,0,1,1,0,0,0,0,
                        1,0,0,0,1,0,0,0,0,0,
                        1,1,0,0,1,0,0,0,0,0,
                        0,1,1,1,1,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,};
    hole holes[5];
    holes[0] = {.x = 1, .y = 1};
    holes[1] = {.x = 1, .y = 2};
    holes[2] = {.x = 2, .y = 1};
    holes[3] = {.x = 3, .y = 1};
    holes[4] = {.x = 4, .y = 1};

    box boxes[5];
    boxes[0] = {.x = 2, .y = 5};
    boxes[1] = {.x = 2, .y = 4};
    boxes[2] = {.x = 3, .y = 3};
    boxes[3] = {.x = 2, .y = 2};
    boxes[4] = {.x = 3, .y = 1};

    player player = {.x = 1, .y = 5};
    clear();
    game(coord, map, player, boxes, holes, 5);
}

void finishMenu(COORD &coord)
{
    Sleep(2000); //2 s
    printFinishMenu();

    char input = getInput();

    if(input == 'r' || input == 27)
    {
        startMenu(coord);
        exit(0);
    }

    finishMenu(coord);
}

void selectMap(COORD &coord)
{
    printSelectMapMenu();

    char input = getInput();
    
    if(input == 'r' || input == 27)
        return;

    if(input == '0') 
    {    
        map0(coord);
        return;
    }
    else if(input == '1')
    {
        map1(coord);
        return;
    }
    else if(input == '2')
    {
        map2(coord);
        return;
    }

    selectMap(coord);
}

void pauseMenu(COORD &coord)
{
    printPauseMenu();

    char input = getInput();
    
    if(input == 'f' || input == 27)
        exit(0);
    
    if(input == 'n')
        selectMap(coord);
    else if(input == 's')
        about();
    else if( input == 'c')
        return;

    pauseMenu(coord);
}

void startMenu(COORD &coord)
{
    printStartMenu();

    char input = getInput();
    
    if(input == 'f' || input == 27)
        return;

    if(input == 'n')
        selectMap(coord);
    else if(input == 's')
        about();

    startMenu(coord);
}

int main()
{
    COORD coord;
    setup(coord);
    startMenu(coord);

    return 0;
}