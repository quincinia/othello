#include "piece.h"
#include "functions.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static int count = 1;

Piece::Piece() {
	if (tY < 8) { //sets the correct cords in the array/board
		m_col = tY++;
		m_row = tX;
	} else {
		tY = 0;
		m_col = tY++;
		tX++;
		m_row = tX;
	}
	
	m_color = ' ';
}

Piece::Piece(char c, int xc, int yc) : m_row(xc), m_col(yc), m_color(c) {
	
}

char Piece::color() const {
	return m_color;
}

void Piece::setcolor(char c) {
	m_color = c;
}

int Piece::row() const {
	return m_row;
}

void Piece::setrow(int x) {
	m_row = x;
}

int Piece::col() const {
	return m_col;
}

void Piece::setcol(int y) {
	m_col = y;
}

void Piece::flip() {
	if (m_color == 'X') {
		m_color = 'O';
	} else {
		m_color = 'X';
	}
}

bool Piece::oob(int x, int y) { 
	if (x > 7 || y > 7 || x < 0 || y < 0) {
		return 1;
	}
	return 0;
}

//moved oob outside of the loops or else it will cause seg fault
//trace now returns bool in the case that a scanned direction was a false positive
//eg. OXO has no valid moves for O
bool Piece::trace(int i, int j, Piece board[][8]) {
	int traceRow = m_row + i;
	int traceCol = m_col + j;
	do {
		//traces along <i, j>, stops when it hits a space, matching color, goes out of bounds, or '+'
		traceRow += i;
		traceCol += j;

		if (oob(traceRow, traceCol)) {return 0;}
	} while (board[traceRow-i][traceCol-j].color() == board[traceRow][traceCol].color());
	
	if (((board[traceRow][traceCol].color() != ' ') || (board[traceRow][traceCol].color() != '+')) && (board[traceRow][traceCol].color() != m_color)) { //only a valid move if the first non-opposite color is ' ' or '+', and the spot isnt already filled by ur color
		board[traceRow][traceCol].setcolor('+');
		board[traceRow][traceCol].pairs.push_back(*this);
		return 1;
	} //note: this will keep placing '+' unless they are cleared beforehand
	return 0;
}

bool Piece::scan(Piece board[][8]) {
	bool valid_move = 0;
	int scanRow = m_row - 1;
	int scanCol = m_col - 1;
	for (; scanRow < (m_row + 2); ++scanRow) {
		for (scanCol = m_col - 1; scanCol < (m_col + 2); ++scanCol) {
			if (oob(scanRow, scanCol)) {continue;} //prevents segfaults
			if ((scanRow == m_row && scanCol == m_col) || 
				 (board[scanRow][scanCol].color() == ' ') || 
				 (board[scanRow][scanCol].color() == m_color) || 
				 (board[scanRow][scanCol].color() == '+')) {
				//out of bounds, same coordinates, no piece, same piece, or '+' placed from previous iterations
				//note: this does not explicitly look for 'X' or 'O', so be sure to reset all valid pieces back to ' ' when a choice is made
				//you could include an opposite color as part of the class, but w.e

				continue;
			} else {
				valid_move = trace(scanRow-m_row, scanCol-m_col, board); //subtract by original cords to get relative position
			}

		}
	}
	return valid_move;
}

void Piece::reversi(Piece board[][8]) {
	int vectorI = 0, vectorJ = 0;
	int travelRow = m_row;
	int travelCol = m_col;
	for(int i = 0; i < pairs.size(); ++i) {
		travelRow = m_row;
		travelCol = m_col;
		vectorI = pairs[i].row() - m_row;
		if (vectorI != 0) {
			vectorI = vectorI/abs(vectorI);
		}
		vectorJ = pairs[i].col() - m_col;
		if (vectorJ != 0) {
			vectorJ = vectorJ/abs(vectorJ);
		}
		//creates the trace vector and turns it into a unit vector <vectorI, vectorJ>
		while((travelRow + vectorI + travelCol + vectorJ) != (pairs[i].row() + pairs[i].col())) {
			travelRow += vectorI;
			travelCol += vectorJ;
			board[travelRow][travelCol].flip();
		}
	}
	pairs.clear();
}
