#include <vector>
#include <iterator>
#include <iostream>
#include <cctype> //isalpha()
#include "include/piece.h" //note: these filepaths have not been tested yet
#include "include/functions.h"
using namespace std;

void printBoard(Piece board[][8]) {
	cout << " | A | B | C | D | E | F | G | H |\n";
	for (int i = 0; i < 8; ++i) {
		cout << "---------------------------------|\n";
		cout << i+1 << "|";
		for (int j = 0; j < 8; ++j) {
			cout << " " << board[i][j].color() << " |";
		}
		cout << "\n";
	}
	cout << "---------------------------------|\n";
}

bool turn(char color, Piece board[][8]) {
	bool valid = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].color() == color) {
				board[i][j].scan(board) ? (valid = 1):0;
			}
		}
	}
	return valid;
}



void place(char color, Piece board[][8]) {
	char input1, input2;
	char line[100];
	int iRow, iCol; //note: the x axis (letters) actually corresponds to the second bracket in the board, so technically the format is board[y][x]
	cout << "Enter coordinates: ";
	do {
	cin >> input1;
	switch (isalpha(input1)) {
		case 0: {
			cin >> input2;
			if (isalpha(input2)) {
				input2 = toupper(input2);
				iRow = input1 - 49;
				iCol = (int)input2 - 65;
			} else {
				iRow = input1-49;
				iCol = input2-49;
			}
			break;
		}
		default: {
			input1 = toupper(input1);
			cin >> input2;
			if (isalpha(input2)) {
				iRow = (int)input1 - 65;
				iCol = (int)input2 - 65;
			} else {
				input2 = toupper(input2);
				iRow = input2-49;
				iCol = (int)input1 - 65;
			}
			break;
		}
	}
	std::cin.getline(line, 99);
	cout << "you selected: (" << iRow << ", " << iCol << ") (" << iRow << ", " << char(iCol+65) << ")\n";	
	} while (board[iRow][iCol].color() != '+' || board[0][0].oob(iRow, iCol));
	board[iRow][iCol].setcolor(color); 
	board[iRow][iCol].reversi(board); 
}

void clearPairs(Piece board[][8]) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].color() == '+') {
				board[i][j].setcolor(' ');
				board[i][j].pairs.clear();
			}
		}
	}
}

int outcome(const int white, const int black) {
	if (white == black) {
		return 0;
	} else if (white > black) {
		return 1;
	}
	return 2;
}
