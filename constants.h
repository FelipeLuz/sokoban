#include <stdio.h>
#include <iostream>

using namespace std;

string BOX[2] = {"[####]", "[####]"}; // char(35);
string HOLE[2] ={"  *  "};
string PLAYER[2] = {" __QQ", "(_)_\">"};
string PLAYER_RIGHT[2] = {" __QQ", "(_)_\">"};
string PLAYER_LEFT[2] = {"QQ__ ", "<\"_(_)"};
const string WALL = string(1,char(219));
const string SPACE = " ";
const string MAPS_FOLDER = "maps/";
const string MAP_EXTENSION = ".txt";
const string SCORES_FOLDER = "scores/";
const string SCORES_EXTENSION = ".csv";