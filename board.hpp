#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "pieces.hpp"

#define BOARD_SIZE 8

// Board Class 
class Board {
public:
	Board() {
		//allocate the vector
		board.resize(BOARD_SIZE);
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}
	}

	void set_turn(bool set)
	{
		turn = set;
	}

	void change_turn()
	{
		turn = !turn;
	}

	bool get_turn()
	{
		return turn; 
	}

	void initialize() 
	{
		Piece* x;

	    //initialize the board configuration
		// Player Pieces 
		x = new TieFighter(Player);
		board[0][2] = x;
		x = new TieFighter(Player);
		board[0][3] = x;
		x = new TieFighter(Player);
		board[0][5] = x;
		x = new TieFighter(Player);
		board[0][6] = x;
		x = new XWing(Player);
		board[2][1] = x;
		x = new XWing(Player);
		board[2][2] = x;
		x = new XWing(Player);
		board[2][6] = x;
		x = new XWing(Player);
		board[2][7] = x;
		x = new Wall(Player);
		board[1][3] = x;
		x = new Wall(Player);
		board[1][5] = x;
		x = new DeathStar(Player);
		board[1][4] = x;

		//put black pieces
		x = new TieFighter(Aphra);
		board[6][2] = x;
		x = new TieFighter(Aphra);
		board[6][3] = x;
		x = new TieFighter(Aphra);
		board[6][5] = x;
		x = new TieFighter(Aphra);
		board[6][6] = x;
		x = new XWing(Aphra);
		board[4][1] = x;
		x = new XWing(Aphra);
		board[4][2] = x;
		x = new XWing(Aphra);
		board[4][6] = x;
		x = new XWing(Aphra);
		board[4][7] = x;
		x = new Wall(Aphra);
		board[5][5] = x;
		x = new Wall(Aphra);
		board[5][3] = x;
		x = new DeathStar(Aphra);
		board[5][4] = x;

		// Number of pieces for both players, there are 4 kinds of pieces. Walls, DeathStar, TieFighters, and XWings
		p_pieces_number.resize(4);
		p_pieces_number[tiefighter] = 4;
		p_pieces_number[xwing] = 4;
		p_pieces_number[wall] = 2;
		p_pieces_number[deathstar] = 1;

		a_pieces_number.resize(4);
		a_pieces_number[tiefighter] = 4;
		a_pieces_number[xwing] = 4;
		a_pieces_number[wall] = 2;
		a_pieces_number[deathstar] = 1;
	}

	Board(Board *b) {
		//allocate the vector
		board.resize(BOARD_SIZE);
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}

		// set pieces
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				set_piece(i, j, b->get_piece(i, j));
			}
		}

		//set parent of the new object
		set_parent(b);

		//set turn of the new object
		turn = !b->get_turn();

		//set piece numbers
		p_pieces_number.resize(4);
		p_pieces_number[xwing] = b->get_piece_number(xwing, Player);
		p_pieces_number[tiefighter] = b->get_piece_number(tiefighter, Player);
		p_pieces_number[wall] = b->get_piece_number(wall, Player);
		p_pieces_number[deathstar] = b->get_piece_number(deathstar, Player);

		a_pieces_number.resize(4);
		a_pieces_number[xwing] = b->get_piece_number(xwing, Aphra);
		a_pieces_number[tiefighter] = b->get_piece_number(tiefighter, Aphra);
		a_pieces_number[wall] = b->get_piece_number(wall, Aphra);
		a_pieces_number[deathstar] = b->get_piece_number(deathstar, Aphra);
	}

	short int get_piece_number(PieceType type, PieceOwner owner) {
		if (owner == Player) {
			return p_pieces_number[type];
		}
		else
		{
			return a_pieces_number[type];
		}
	}

	void set_piece_number(PieceType type, PieceOwner owner, int value) {
		if (owner == Player) {
			p_pieces_number[type] += value;
		}
		else {
			a_pieces_number[type] += value;
		}
	}

	void print() {
		for (int i = BOARD_SIZE - 2; i >= 0; --i) 
		{
			cout << i + 1 << " ";
			for (int j = 1; j < BOARD_SIZE; ++j) {
				if (board[i][j] != NULL) {
					board[i][j]->print();
				}
				else {
					cout << " - ";
				}
			}
			if (i == 7)
			{
				cout << "	Aphra";
			}
			else if (i == 0)
			{
				cout << "	Player";
			}
			cout << endl;
		}
		cout << "   A  B  C  D  E  F  G " << endl;
		cout << endl;
	}


	Piece* get_piece(int x, int y)
	{
		return board[x][y];
	}
	
	void set_piece(int x, int y, Piece* p) 
	{
		board[x][y] = p;
	}

	vector<vector<Piece*> > get_board()
	{
		return board;
	}

	Board* move_piece(int src_x, int src_y, int dest_x, int dest_y)
	{
		Board *new_board = new Board(this);

		Piece* src = new_board->get_piece(src_x, src_y);
		Piece* dest = new_board->get_piece(dest_x, dest_y);

		// Remove the piece we are overtaking and update pieces
		if (dest != NULL)
		{
			new_board->set_piece_number(dest->get_type(), dest->get_owner(), -1);
		}

		new_board->set_piece(dest_x, dest_y, src);
		new_board->set_piece(src_x, src_y, NULL);

		return new_board;
	}

	Board* move(int src_x, int src_y, int dest_x,
		 int dest_y) {

		// get the piece we are moving
		Piece* src = get_piece(src_x, src_y);
		// Check if there is a piece at the destination now as well
		Piece* dest = get_piece(dest_x, dest_y);

		// Check for Piece Chosen
		if (src == NULL) {
			cout << "No Piece Chosen To Move, Invalid Destination" << endl;
			return NULL;
		}

		// Check if moving to the same location
		if (src_x == dest_x && src_y == dest_y) {
			cout << "User must make a move" << endl;
			return NULL;
		}

		// Movement for the X Wings and Tie Fighters and Making sure the Deathstar and Walls Don't move	

		// Tie Fighters can move like Rooks in Chess. Meaning they can go Left, Right, Up, and Down. 
		// We need to test the conditions for each movement.... here we go :( 
		if (src->get_type() == tiefighter)
		{
			// Check #1: see if the piece is moving Left or Right (Horizontal) 
			// So we know that our controls are inversed x = y, y = x. so if the X does not change we are moving Left or Right. 
			if (src_x == dest_x)
			{
				//Check Moving to the Right 
				if (dest_y > src_y)
				{
					// First Condition is if our path is being blocked. 
					for (int i = src_y + 1; i < dest_y; ++i)
					{
						// If there is any piece, whether it is our piece or Aphra's piece we cannot move to that location and say the move is not legal 
						// It may have been wiser to suggest moving to capture a piece in a later form of the code. just a thought. 
						if (get_piece(src_x, i) != NULL)
						{
							cout << "There is a piece in your path" << endl;
							return NULL;
						}
					}
				}
				// Same concepts apply for moving to the left. 
				else if (dest_y < src_y)
				{
					for (int i = src_y - 1; i > dest_y; --i) {
						if (get_piece(src_x, i) != NULL)
						{
							cout << "There is a piece in your path" << endl;
							return NULL;
						}
					}
				}

				// From here we have to check if there is an enemy piece in the way that we can overtake. 
				// We will need a special case for the deathstar to check if the location we are taking it is from behind or not.

				// First case is there is nothing at the destination
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y); // Move to the position
				}
				// Second case is checking if we can move to the destination 
				else if (dest->get_owner() != src->get_owner())
				{
					// Special Case for the walls, we do not need to worry about the death star at this point since this is Horizontal movement. we will check in vertical movement
					if (dest->get_type() == wall)
					{
						cout << "You cannot capture a wall" << endl;
						return NULL;
					}
					// Else we can go ahead and move the piece. 
					return move_piece(src_x, src_y, dest_x, dest_y);
				}
				else
				{
					cout << "Red On Red!" << endl;
					return NULL;
				}
			}
			// Next we check Vertical movements of up and down. 
			// First we will check in the up direction 
			else if (src_y == dest_y)
			{
				if (dest_x > src_x)
				{
					// Check positions between the piece and the destination
					for (int i = src_x + 1; i < dest_x; ++i) {
						if (get_piece(i, src_y) != NULL)
						{
							cout << "There is a piece blocking the path chosen" << endl;
							return NULL;
						}
					}
				}
				else if (dest_x < src_x) { //move down
					for (int i = src_x - 1; i > dest_x; --i) {
						if (get_piece(i, src_y) != NULL)
						{
							cout << "There is a piece in the way of your destination please try again" << endl;
							return NULL;
						}
					}
				}

				// Now we have special tests for both ways, We cannot move to a location with a wall. and we need to check if we can move to the destination of there is a 
				// deathstar since we an only capture it from the back end.

				// First Check Condition is if the spot is empty or not. 
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				}
				// Now we check if there is a piece there already. 
				else if (dest->get_owner() != src->get_owner())
				{
					if (dest->get_type() == deathstar && src_x > dest_x)
					{
						cout << "you cannot overtake the deathstar from the front" << endl;
						return NULL;
					}
					else if (dest->get_type() == wall)
					{
						cout << "cannot overtake a wall" << endl;
						return NULL;
					}

					return move_piece(src_x, src_y, dest_x, dest_y);
				}
				else
				{
					cout << "cannot overtake your own pieces" << endl;
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}

		// The second piece that is able to move for us are the X Wings which move similar to that of a bishop piece. 
		else if (src->get_type() == xwing)
		{
			// So when moving vertical. we know the difference between the values from whatever location we move to should be the same. 
			// So Absolute Value of Source - Destination. Tadaaaa~~
			
			// Because Athena hates me. 
			int sd_x = src_x - dest_x;
			int sd_y = src_y - dest_y;
			int ds_x = dest_x - src_x;
			int ds_y = dest_y - src_y; 

			if (sd_x < 0)
			{
				sd_x = sd_x * -1;
			}

			if (sd_y < 0)
			{
				sd_y = sd_y * -1;
			}
			
			if (ds_x < 0)
			{
				ds_x = ds_x * -1;
			}
			
			if (ds_y < 0)
			{
				ds_y = ds_y * -1;
			}

			if (sd_x == sd_y)
			{
				// Moving Right
				if (dest_x > src_x)
				{
					// Up - Right 
					if (dest_y > src_y)
					{
						for (int i = 1; i < ds_x; ++i)
						{
							if (get_piece(src_x + i, src_y + i) != NULL)
							{
								cout << "There is a piece in the way of our destination so we cannot move" << endl;
								return NULL;
							}
						}
					}
					// Down - Right - Need to check here for the case of a deathstar on movement. 
					else if (dest_y < src_y)
					{
						for (int i = 1; i < ds_x; ++i)
						{
							if (get_piece(src_x + i, src_y - i) != NULL)
							{
								cout << "There is a piece in the way of our destination" << endl;
								return NULL;
							}
						}
					}
					/* I am unsure if I will need this one, check later.
					else
					{
					return NULL;
					}
					*/

					// If nothing is in the way of our destination
					if (dest == NULL && dest_y > src_y)
					{
						return move_piece(src_x, src_y, dest_x, dest_y);
					}
					else if (dest == NULL && src_y > dest_y)
					{
						cout << "Can only move back to capture";
						return NULL; 
					}
					else if (dest->get_owner() != src->get_owner())
					{
						if (dest->get_type() == deathstar && dest_y < src_y)
						{
							cout << "Cannot take deathstar from the front" << endl;
							return NULL;
						}
						else if (dest->get_type() == wall)
						{
							cout << "Cannot overtake a wall" << endl;
							return NULL;
						}

						return move_piece(src_x, src_y, dest_x, dest_y);
					}
					else
					{
						cout << "Red On Red" << endl;
						return NULL;
					}
				}
				else if (dest_x < src_x)
				{
					// Up Left
					if (dest_y > src_y)
					{
						for (int i = 1; i < ds_x; ++i)
						{
							if (get_piece(src_x - i, src_y + i) != NULL)
							{
								cout << "A piece is blocking the x-wing" << endl;
								return NULL;
							}
						}
					}
					// Down Left
					else if (dest_y < src_y)
					{
						for (int i = 1; i < ds_x; ++i)
						{
							if (get_piece(src_x - i, src_y - i) != NULL)
							{
								cout << "There is a piece blocking the x-wing" << endl;
								return NULL;
							}
						}
					}

					/* May need these. Test it for a bit and think about it.
					else
					{
					cout << "Bishop cannot move. Err:7" << endl;
					return NULL;
					}
					*/

					// We need a special case here for if we are heading downward or upward to the deathstar
					if (dest == NULL && dest_y < src_y)
					{
						return move_piece(src_x, src_y, dest_x, dest_y);
					}
					else if (dest->get_owner() != src->get_owner())
					{
						if (dest->get_type() == deathstar && src_y < dest_y)
						{
							cout << "cannot attack deathstar from the front" << endl;
							return NULL;
						}
						else if (dest->get_type() == wall)
						{
							cout << "cannot overtake a wall" << endl;
							return NULL;
						}
						return move_piece(src_x, src_y, dest_x, dest_y);
					}
					else {//cannot eat the same color
						  //						cout << "Bishop cannot move.Err:8" << endl;
						return NULL;
					}
				}
				else {
					//					cout << "Bishop cannot move. Err:9" << endl;
					return NULL;
				}
			}
			else {
				//				cout << "Bishop cannot move. Err:10" << endl;
				return NULL;
			}
		}
		// Just making sure they don't try to move walls or the deathstar
		else if (src->get_type() == wall)
		{
			return NULL;
		}
		else if (src->get_type() == deathstar)
		{
			return NULL;
		}
		return NULL;
	}

	int evaluate(PieceOwner owner)
	{
		Board* move = NULL;
		int score = 0;
		int value = 0; 
		int pieces = 0;

		if (owner == Player)
		{
			score += (TieFighter::value * (4 - get_piece_number(tiefighter, Aphra)));
			score += (XWing::value * (4 - get_piece_number(xwing, Aphra)));
			score += (Wall::value * (4 - get_piece_number(wall, Aphra)));
			score += (DeathStar::value * (4 - get_piece_number(deathstar, Aphra)));
		}
		else
		{
			score += (TieFighter::value * (4 - get_piece_number(tiefighter, Player)));
			score += (XWing::value * (4 - get_piece_number(xwing, Player)));
			score += (Wall::value * (4 - get_piece_number(wall, Player)));
			score += (DeathStar::value * (4 - get_piece_number(deathstar, Player)));
		}
		
		if (owner == Player)
		{
			pieces = p_pieces_number.size();
		}
		else
		{
			pieces = a_pieces_number.size();
		}

		value = (score + pieces) / 2;
		
		return value;
	}

	Board* get_parent() {
		return parent;
	}

	void set_parent(Board* parent) {
		this->parent = parent;
	}

	vector<Board*>* list_all_moves() 
	{
		vector<Board*> *moves = new vector<Board*>();
		Board* temp = NULL;
		PieceOwner turn = get_turn() ? Player : Aphra;

		for (int i = 0; i < 7; ++i) {

			for (int j = 0; j < 8; ++j) {
				if (get_piece(i, j) != NULL && get_piece(i, j)->get_owner()
					== turn) {
					for (int k = 0; k < 7; ++k) {
						for (int l = 0; l < 8; ++l) {
							if (i == k && j == l) {
								continue;
							}
							if ((temp = move(i, j, k, l)) != NULL) {
								moves->push_back(temp);
								change_turn();
							}
						}
					}
				}
			}
		}

		return moves;
	}

private:
	vector<vector<Piece*> > board;
	Board* parent;
	bool turn;
	vector<short int> p_pieces_number;
	vector<short int> a_pieces_number;
};

#endif