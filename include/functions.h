#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <vector>
using namespace std;



void printBoard(Piece board[][8]);

bool turn(char color, Piece board[][8]);

void place(char color, Piece board[][8]);

void clearPairs(Piece board[][8]);

int outcome(const int white, const int black);

#endif