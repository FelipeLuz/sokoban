/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "conmanip.h"

using namespace conmanip;
using namespace std;

void pauseMenu(COORD &coord);
void startMenu(COORD &coord);

string BOX[2] = {"[==]", "[XX]"}; // char(35);
string HOLE[2] ={" __ ", "(__)"};
string PLAYER[2] = {" __QQ", "(_)_\">"};
const string WALL = string(1,char(219));
const string SPACE = " ";

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

void clear()
{
    system("cls");
}

char getInput()
{
    //if ( _kbhit() )
    return getch();
}

void printCenter(string output)
{
    console_out_context ctxout;
    console_out conout(ctxout);
    int middle = conout.getsize().X/2;
    cout << setposx(middle - output.length()/ 2) << output;
    ctxout.restore(console_cleanup_options::restore_attibutes);
}

void printAtMultiline(int x, int y, string val[], int lineCount, console_text_colors color )
{
    for (int i = 0; i < lineCount; i++)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y+i;
        console_out_context ctxout;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << settextcolor(color) << val[i];
        ctxout.restore(console_cleanup_options::restore_attibutes);
    }
}

void printAt(int x, int y, string val, console_text_colors color)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    console_out_context ctxout;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << settextcolor(color) << val;
    ctxout.restore(console_cleanup_options::restore_attibutes);
}

void printPlayer(COORD &coord, player player)
{
    printAtMultiline(player.x*6, player.y*2, PLAYER, 2,console_text_colors::green);
}

void printBoxes(COORD &coord, box boxes[], int boxCount)
{
    for(int i = 0; i < boxCount; i++)
    {
        printAtMultiline(boxes[i].x*6 + 1, boxes[i].y*2, BOX, 2, (console_text_colors) (i + 2));
    }
}

void printHoles(COORD &coord, hole holes [], int holeCount)
{
    for(int i = 0; i < holeCount; i++)
    {
        printAtMultiline(holes[i].x *6 + 1, holes[i].y*2, HOLE, 2, console_text_colors::red);
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

player move(char input, player lastPos, box boxes[], int boxSize,int map[10][10])
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
    return canMove ? newPos : lastPos;
}

void finish()
{
    clear();
    printf("You finished the game!\n");
    printf("(R)eturn\n");

    char input = getInput();

    if(input == 'r')
        return;

    finish();
}

void about()
{
    clear();
    printf("Felipe Luz - 5975425\n");
    printf("Abril/2023\n");
    printf("Abril/2023\n");
    printf("(V)oltar\n");

    char input = getInput();

    if(input == 'v')
        return;
}

void game(COORD &coord, int map[10][10], player player, box boxes[], hole holes[], int boxCount)
{
    printMap(coord, map);
    printHoles(coord, holes, boxCount);
    printPlayer(coord, player);
    printBoxes(coord, boxes, boxCount);
    
    char input = getInput();
    
    if(input == 27) 
        pauseMenu(coord);

    player = move(input, player, boxes, boxCount, map);

    if(checkComplete(boxes, holes, boxCount))
    {
        finish();
        return;
    }

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
    holes[0] = {7, 3};
    holes[1] = {7, 4};
    holes[2] = {7, 5};

    box boxes[3];
    boxes[0] = {2, 6};
    boxes[1] = {2, 5};
    boxes[2] = {3, 6};

    player player = {.x = 1, .y = 7};

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
    holes[0] = {1, 6};
    holes[1] = {1, 7};
    holes[2] = {2, 6};
    holes[3] = {2, 7};

    box boxes[4];
    boxes[0] = {2, 4};
    boxes[1] = {3, 6};
    boxes[2] = {4, 5};
    boxes[3] = {4, 2};

    player player = {.x = 6, .y = 2};

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
    holes[0] = {1, 1};
    holes[1] = {1, 2};
    holes[2] = {2, 1};
    holes[3] = {3, 1};
    holes[4] = {4, 1};

    box boxes[5];
    boxes[0] = {2, 5};
    boxes[1] = {2, 4};
    boxes[2] = {3, 3};
    boxes[3] = {2, 2};
    boxes[4] = {3, 1};

    player player = {.x = 1, .y = 5};

    game(coord, map, player, boxes, holes, 5);
}

void selectMap(COORD &coord)
{
    clear();
    printf("\n\n\n");
    printCenter(" _________________________ \n");
    printCenter("(__| |_______________| |__)\n");
    printCenter("   | |    Sokoban    | |   \n");
    printCenter("   | |_______________| |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |  (0) Mapa 0   | |   \n");
    printCenter("   | |  (1) Mapa 1   | |   \n");
    printCenter("   | |  (2) Mapa 2   | |   \n");
    printCenter("   | |  (R)etornar   | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");

    char input = getInput();
    
    if(input == 'r')
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
    clear();
    printf("\n\n\n");
    printCenter(" _________________________ \n");
    printCenter("(__| |_______________| |__)\n");
    printCenter("   | |    Sokoban    | |   \n");
    printCenter("   | |_______________| |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |  (N)ovo Jogo  | |   \n");
    printCenter("   | |  (C)ontinuar  | |   \n");
    printCenter("   | |  (S)obre      | |   \n");
    printCenter("   | |  (F)im        | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");

    char input = getInput();
    
    if(input == 'f')
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
    clear();
    printf("\n\n\n");
    printCenter(" _________________________ \n");
    printCenter("(__| |_______________| |__)\n");
    printCenter("   | |    Sokoban    | |   \n");
    printCenter("   | |_______________| |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |  (N)ovo Jogo  | |   \n");
    printCenter("   | |  (S)obre      | |   \n");
    printCenter("   | |  (F)im        | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");

    char input = getInput();
    
    if(input == 'f')
        return;

    if(input == 'n') //Todo add map selection
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