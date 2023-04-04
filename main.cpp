/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
*/
#include <iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

const char BOX = 'B';
const char HOLE = '*';
const char PLAYER = char (2);
const char WALL = char(219);

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
    setFontSize(50, 50);
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

void printAt(int x, int y, char val)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << val;
}

void printPlayer(COORD &coord, player player)
{
    printAt(player.x, player.y, PLAYER);
}

void printBoxes(COORD &coord, box boxes[], int boxCount)
{
    for(int i = 0; i < boxCount; i++)
    {
        printAt(boxes[i].x, boxes[i].y, BOX);
    }
}

void printHoles(COORD &coord, hole holes [], int holeCount)
{
    for(int i = 0; i < holeCount; i++)
    {
        printAt(holes[i].x, holes[i].y, HOLE);
    }
}

void printMap(COORD &coord, int map[10][10])
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            switch (map[i][j])
            {
                case 0: 
                    cout<<" "; 
                    break;
                case 1: 
                    cout<< WALL; 
                    break;
 
            }
        }
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

bool checkInteraction(int map[10][10], player player, box boxes[], int boxCount, int xMove, int yMove)
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
    
    bool canMove = checkPlayerMove(map, newPos) && checkInteraction(map, newPos, boxes, boxSize, xMove, yMove);
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
}

void game(COORD &coord, int map[10][10], player player, box boxes[], hole holes[], int boxCount)
{
    printMap(coord, map);
    printHoles(coord, holes, boxCount);
    printPlayer(coord, player);
    printBoxes(coord, boxes, boxCount);
    
    char input = getInput();
    if(input == 27) // esc
        return;

    player = move(input, player, boxes, boxCount, map);

    if(checkComplete(boxes, holes, boxCount))
    {
        finish();
        return;
    }

    game(coord, map, player, boxes, holes, boxCount);
}

void startGame(COORD &coord)
{
    int map[10][10]={ 1,1,1,1,1,1,1,1,1,1,
                    1,0,1,0,0,0,0,0,0,1,
                    1,0,1,0,0,0,0,0,0,1,
                    1,0,1,1,1,1,0,0,0,1,
                    1,0,0,0,0,1,0,0,0,1,
                    1,0,0,1,0,1,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1 };
    int boxCount = 3;
    box boxes[boxCount];
    boxes[0] = {7, 8};
    boxes[1] = {7, 7};
    boxes[2] = {6, 6};

    hole holes[boxCount];
    holes[0] = {1, 8};
    holes[1] = {1, 7};
    holes[2] = {1, 6};

    player player = {.x = 5, .y = 5};

    game(coord, map, player, boxes, holes, boxCount);

}

void about()
{
    clear();
    printf("Felipe Luz - 5975425\n");
    printf("(R)eturn\n");

    char input = getInput();

    if(input == 'r')
        return;
}

void menu(COORD &coord)
{
    clear();
    printf("(N)ew Game\n");
    printf("(A)bout\n");
    printf("(E)xit\n");

    char input = getInput();
    
    if(input == 'e')
        return;
    
    if(input == 'n') //Todo add map selection
        startGame(coord);
    else if(input == 'a')
        about();

    menu(coord);
}

int main()
{
    COORD coord;
    setup(coord);
    menu(coord);

    return 0;
}