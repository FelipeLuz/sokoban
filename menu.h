#include <stdio.h>
#include <iostream>
#include "print.h"
#include "terminal.h"

using namespace std;

void tutorial()
{
	clear();
    printf("\n\n\n");
    printCenter(" _________________________ \n");
    printCenter("(__| |_______________| |__)\n");
    printCenter("   | |    Sokoban    | |   \n");
    printCenter("   | |_______________| |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |   Tutorial    | |   \n");
    printCenter("   | |               | |   \n");
	printCenter("   | | Mover:        | |   \n");
	printCenter("   | |   * W,A,S,D   | |   \n");
	printCenter("   | |   * Setas     | |   \n");
	printCenter("   | |               | |   \n");
	printCenter("   | | Sair:         | |   \n");
	printCenter("   | |   * ESC       | |   \n");
	printCenter("   | |               | |   \n");
    printCenter("   | | Objetivo:     | |   \n");
    printCenter("   | |   * Levar as  | |   \n");
    printCenter("   | |     caixas ate| |   \n");
    printCenter("   | |     o local   | |   \n");
	printCenter("   | |               | |   \n");
    printCenter("   | |  (R)etornar   | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");

    char input = getInput();

    if(input == 'r' || input == 27)
        return;

	tutorial();
}

void printFinishMenu()
{
    clear();
    printf("\n\n\n");
    printCenter(" __________________________ \n");
    printCenter("(__| |________________| |__)\n");
    printCenter("   | |     Sokoban    | |   \n");
    printCenter("   | |________________| |   \n");
    printCenter("   | |                | |   \n");
    printCenter("   | | Voce completou | |   \n");
    printCenter("   | |    a fase!     | |   \n");
    printCenter("   | |                | |   \n");
    printCenter("   | |   (R)etornar   | |   \n");
    printCenter(" __| |________________| |__ \n");
    printCenter("(__|_|________________|_|__)\n");
}


void about()
{
    clear();
    printf("\n\n\n");
    printCenter(" _________________________ \n");
    printCenter("(__| |_______________| |__)\n");
    printCenter("   | |    Sokoban    | |   \n");
    printCenter("   | |_______________| |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |  Felipe Luz   | |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | | Alg. Prog. II | |   \n");
    printCenter("   | |  Abril/2023   | |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |   Professor:  | |   \n");
    printCenter("   | |  Thiago F. P. | |   \n");
    printCenter("   | |               | |   \n");
    printCenter("   | |  (T)utorial   | |   \n");
	printCenter("   | |  (R)etornar   | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");

    char input = getInput();

    if(input == 'r' || input == 27)
        return;
	
	if(input == 't')
        tutorial();

	about();
}

void printSelectMapMenu()
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
	printCenter("   | |               | |   \n");
    printCenter("   | |  (R)etornar   | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");
}


void printPauseMenu()
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
	printCenter("   | |               | |   \n");
    printCenter("   | |  (F)im        | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");
}

void printStartMenu()
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
	printCenter("   | |               | |   \n");
    printCenter("   | |  (F)im        | |   \n");
    printCenter(" __| |_______________| |__ \n");
    printCenter("(__|_|_______________|_|__)\n");
}