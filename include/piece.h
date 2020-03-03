#ifndef PIECES_H_
#define PIECES_H_
#include <vector>

class Piece {
	public: 
		Piece();
		Piece(char c, int xc = 0, int yc = 0);

		//getters + setters
		char color() const;
		void setcolor(char c);

		int row() const;
		void setrow(int r);

		int col() const;
		void setcol(int y);

		//changes from X->O or O->X
		void flip();

		//used to set coordinates of all the pieces
		static int tX;
		static int tY;
		

		//scans the surrounding 8 spaces for a color of the (opposite type)***
		//***see piece.cpp
		//if scan returns 0, display "no available moves" (in main)
		//if available move is found, calls trace() to verify
		bool scan(Piece board[][8]);

		std::vector<Piece> pairs; //used to keep track of which pieces need to be flipped when a move is selected
		bool oob(int x, int y); //out of bounds

		void reversi(Piece board[][8]);
	private:
		int m_row;
		int m_col;
		//where 0,0 is the top right
		char m_color;
		
		//traces along the vector created by scan() until it finds a valid move, then marks it with '+' and adds to its pair vector
		bool trace(int i, int j, Piece board[][8]);
		
};

#endif
