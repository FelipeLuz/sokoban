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
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace conmanip;
using namespace std;
typedef pair<string, int> PlayerScore;

void finishMenu(COORD &coord, int moveCount, string playerName);
void pauseMenu(COORD &coord, string playerName, history oldHistory);
void startMenu(COORD &coord, string playerName);

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

bool sortScores(const PlayerScore &a, const PlayerScore &b) 
{
    return (a.second < b.second);
}

void saveScore(string mapName, string playerName, int moveCount) 
{
    vector<PlayerScore> scores;
    string path =  SCORES_FOLDER + mapName + SCORES_EXTENSION;
    ifstream file(path);
    string line, name;
    int moves;

    if (file.is_open())
    {
        while (getline(file, line)) 
        {
            stringstream ss(line);
            getline(ss, name, ',');
            ss >> moves;

            scores.push_back(make_pair(name, moves));
        }
    }
    file.close();
    
    scores.push_back(make_pair(playerName, moveCount));
    sort(scores.begin(), scores.end(), sortScores);
   
    ofstream outputFile(path);
    if (outputFile.is_open())
    {
        for (const auto& score : scores) 
        {
            outputFile << score.first << "," << score.second << "\n";
        }
    }

    outputFile.close();
}

void clearMoves() {

    ofstream file("moves.csv");

    file.close();
}

void gameV2(COORD &coord, assets assets, history history)
{
    printMap(coord, assets.map);
    printHoles(coord, assets.holes, assets.boxCount);
    printPlayer(coord, assets.player);
    printBoxes(coord, assets.boxes, assets.boxCount);
    
    if(checkComplete(assets.boxes, assets.holes, assets.boxCount))
    {
        saveScore(assets.mapName, assets.playerName, assets.moveCount);
        finishMenu(coord, assets.moveCount, assets.playerName);
        return;
    }

    char input = getInput();
    
    if(input == 27) 
        pauseMenu(coord, assets.playerName, history);

    assets = move(input, assets, history);
    
    gameV2(coord, assets, history);
}

assets readMapFileV2( assets pAssets, string mapName )
{
    ifstream stream;
    string mapPath = MAPS_FOLDER + mapName + MAP_EXTENSION;
    int currBox = 0;
    int currHole = 0;
    stream.open(mapPath);

    if (stream.is_open()){
        stream>>pAssets.player.x;
        stream>>pAssets.player.y;
        for(int i=0; i<10; i++){
            for(int j=0; j<10; j++){
                int cell;
                stream >> cell;

                if(cell == 2)
                {
                    pAssets.boxes[currBox] = {.x = j, .y = i};
                    currBox++;
                }
                else if(cell == 3)
                {
                    pAssets.holes[currHole] = {.x = j, .y = i};
                    currHole++;
                }
                else if(cell == 4)
                {
                    pAssets.holes[currHole] = {.x = j, .y = i};
                    pAssets.boxes[currBox] = {.x = j, .y = i};
                    currBox++;
                    currHole++;
                }

                if(cell == 1)
                {
                    pAssets.map[i][j] = cell;
                }
                else
                {
                    pAssets.map[i][j] = 0;
                }
            }
        }
    }
    stream.close();
    pAssets.boxCount = currBox;
    return pAssets;
}

void loadMap(COORD &coord, string mapName, string playerName)
{
    assets assets;
    history history;
    assets.init();
    assets.moveCount = 0;
    assets.mapName = mapName;
    assets.playerName = playerName;

    assets = readMapFileV2(assets, mapName);
    history.assets.push_back(assets);
    clear();
    gameV2(coord, assets, history);
}

void finishMenu(COORD &coord, int moveCount, string playerName)
{
    Sleep(2000); //2 sec
    printFinishMenu(moveCount);

    char input = getInput();

    if(input == 'r' || input == 27)
    {
        startMenu(coord, playerName);
        exit(0);
    }

    finishMenu(coord, moveCount, playerName);
}

void selectMap(COORD &coord, string playerName)
{
    clearMoves();
    printSelectMapMenu();

    char input = getInput();
    string map = "map";

    switch (input)
    {
        case 'r':
        case 27:
            return;

        case '0':
        case '1':
        case '2':
            loadMap(coord, map.append(1, input), playerName);
            break;
    
    default:
        selectMap(coord, playerName);
    }
}

void pauseMenu(COORD &coord, string playerName, history oldHistory)
{
    printPauseMenu();

    char input = getInput();
    
    if(input == 'f' || input == 27)
        exit(0);
    
    if(input == 'n')
        selectMap(coord, playerName);
    else if(input == 's')
        about();
    else if( input == 'v')
    {
        clear();
        int step = 0;
        cout << "Voce deu " << oldHistory.assets.back().moveCount << " passos, quantos movimentos quer voltar? " << endl;
        cin >> step;

        if( step >= oldHistory.assets.back().moveCount)
        {
            history newHistory;
            newHistory.assets.push_back(oldHistory.assets[0]);
            return gameV2(coord, oldHistory.assets[0], newHistory);
        }

        for (int i = 0; i < step; i++)
            oldHistory.assets.pop_back();

        return gameV2(coord, oldHistory.assets.back(), oldHistory);
    }
    else if( input == 'c')
        return;

    pauseMenu(coord, playerName, oldHistory);
}

void startMenu(COORD &coord, string playerName)
{
    printStartMenu();

    char input = getInput();
    
    if(input == 'f' || input == 27)
        return;

    if(input == 'n')
        selectMap(coord, playerName);
    else if(input == 's')
        about();

    startMenu(coord, playerName);
}

int main()
{
    clearMoves();
    string playerName;
    cout << "Entre seu nome: ";
    cin >> playerName;

    COORD coord;
    setup(coord);
    startMenu(coord, playerName);

    return 0;
}