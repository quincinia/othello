#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <vector>
using namespace std;


//does what it says
void printBoard(Piece board[][8]);

//returns 1 if there are valid moves for that piece
bool turn(char color, Piece board[][8]);

//gets coordinates from user, updates board if those coordinates correspond to a valid move
void place(char color, Piece board[][8]);

//removes all valid move markers
void clearPairs(Piece board[][8]);

//returns 0 for tie, 1 for white win, 2 for black win
int outcome(const int white, const int black);

#endif
