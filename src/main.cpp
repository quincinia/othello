//most of the x's and y's are flipped
//todo: fix functions to work under the board[y(number)][x(letter)] system

//try to make things in row column format

#include <iostream>
#include <vector>
#include <iterator>
#include "piece.h"
#include "functions.h"
using namespace std;

int Piece::tX = 0;
int Piece::tY = 0;

int main() {
	int whiteCount = 0, blackCount = 0;
  Piece board[8][8];
	//cout << "piece (0, 1): " << board[0][1].row() << " " << board[0][1].col() << endl;
	//board[0][1].setcolor('1');
	board[3][3].setcolor('O');
	board[4][4].setcolor('O');
	board[3][4].setcolor('X');
	board[4][3].setcolor('X');
	/*board[2][3].setcolor('X');
	board[2][4].setcolor('O');
	board[0][0].setcolor('X');
	board[0][1].setcolor('O');*/
	//board[1][3].setcolor('O');

	//printBoard(board);
	//cout << "size check: " << board[0][0].pairs.size();

	//game loop:
	//while both players have valid moves:
		//check whites valid moves
			//if yes, show valid moves and prompt to pick
				//convert (num, alpha) or (alpha, num) to correct cords, check if that cord matches a valid spot, and place there if it is (error msg if not)
				//if a valid spot is picked, flip all pieces between it and its pairs, and clear its pairs vector
				//reset all valid spots to ' ' and clear their pairs vector before starting black's turn
			//if no valid moves, skip to black's turn
		//black's turn is the same as whites

//return 0;
char input[100];
bool whiteTurn = 1;
bool blackTurn = 1;
while (whiteTurn == 1 || blackTurn == 1) {
	
	whiteTurn = turn('O', board);
	printBoard(board);
	cout << "White (O) to move\n";
	if (whiteTurn == 1) {
		place('O', board);
		clearPairs(board);
	} else {
		cout << "No valid moves.\n";
	}
	
	blackTurn = turn('X', board);
	printBoard(board);
	cout << "Black (X) to move\n";
	if (blackTurn == 1) {
		place('X', board);
		clearPairs(board);
	} else {
		cout << "No valid moves.\n";
	}
}
for (int i = 0; i < 8; ++i) {
	for (int j = 0; j < 8; ++j) {
		(board[i][j].color() == 'O') ? ++whiteCount : 0;
		(board[i][j].color() == 'X') ? ++blackCount : 0;
	}
}
cout << "Game over!\n";
switch (outcome(whiteCount, blackCount)) {
	case 0: {
		cout << "Tie!\nWhite " << whiteCount << " - " << blackCount << " Black\n";
		break;
	}

	case 1: {
		cout << "White wins!\nWhite " << whiteCount << " - " << blackCount << " Black\n";
		break;
	}

	case 2: {
		cout << "Black wins!\nBlack " << blackCount << " - " << whiteCount << " White\n";
		break;
	}
}
}