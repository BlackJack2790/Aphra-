// Derek Irvin
// Professor Gordon
// Assignment 2 Project Aphra
// Main File

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "board.hpp"
#include "pieces.hpp"
#include "minimax.hpp"

// declarations for the conversion of the input of the user's move and output of aphra's move
int convert_x(char input_x, int output_x);
int convert_y(char input_y, int output_y);

/*
// If the computer would stop making illegal moves i'd like to test this. 
char revert_x(int input_x, char output_x);
char revert_x(int input_y, char output_y);

void testWin();
*/

int main()
{
	//1. First asks the human whether they would like to move first or second
	// Going on the assumption the user enters a value 1 or 2 and not any other value. 
	int goFirst;
	cout << "I wanna play a game. Would you like to go first or shall I? (1 to go first, 2 to go second) " << endl;

	cin >> goFirst;

	// The current position displayed on the screen before and after each move
	// axes labeled like example
	Board *b = new Board(); // Create a pointer to a board object
	Board *test;	// create a test
	b->initialize();
	cout << "Board:" << endl;
	b->print();

	if (goFirst == 1)
	{
		b->set_turn(true);
	}
	else
	{
		b->set_turn(false);
	}

	// Keeping track of locations 
	// src (x,y) -> dest(x,y)
	char src_x = 0, src_y = 0, dest_x = 0, dest_y = 0;
	// converted locations
	int csrc_x = 0, csrc_y = 0, cdest_x = 0, cdest_y = 0;
	// reverted locations
	char rsrc_x = 0, rsrc_y = 0, rdest_x = 0, rdest_y = 0;

	// 
	while (true) 
	{
		// Player's Turn
		if (b->get_turn() == true)
		{
			cout << "Enter your move XYXY Form: ";
			// Input Backwards. Thank You 133 for something other than a massive panic attack
			cin >> src_y >> src_x >> dest_y >> dest_x;
			cout << endl;

			cdest_x = convert_x(dest_x, cdest_x);
			csrc_x = convert_x(src_x, csrc_x);
			csrc_y = convert_y(src_y, csrc_y);
			cdest_y = convert_y(dest_y, cdest_y);

			// Test the input to see if it is valid
			test = b->move(csrc_x, csrc_y, cdest_x, cdest_y);

			if (test == NULL)
			{
				// Just to yell at them one more time for putting in a stupid request
				cout << "Invalid move. Try again." << endl << endl;
			}
			else
			{
				// apply and print the move
				b = test;
				b->print(); 
				//testWin();
			}
		}
		// Aphra's Turn
		else if (b->get_turn() == false)
		{
			// Machine Overlord's Turn 
			b = ABMinMax(b, 5); // Send the state of the board and depth to go to. 
			
			if (b != NULL)
			{
				b->print();
				// Print the computers move here by following what piece it moved where
				//*********************************************
				// Need a way to save aphra's moves
				//*********************************************
				src_x += '1';
				dest_x += '1';
				src_y += 'A';
				dest_y += 'A';
				cout << "Aphras move is" << src_x << src_y << dest_x << dest_y << endl;
				//testWin(); // test for win after move is made 
			}
			else
			{
				// If it can't find a move check the winning conditions
				//testWin(b->get);

			}

		}
	}

	return 0; 
}

int convert_x(char input_x, int output_x)
{
	if (input_x == '1') {
		output_x = 0;
	}
	else if (input_x == '2') {
		output_x = 1;
	}
	else if (input_x == '3') {
		output_x = 2;
	}
	else if (input_x == '4') {
		output_x = 3;
	}
	else if (input_x == '5') {
		output_x = 4;
	}
	else if (input_x == '6') {
		output_x = 5;
	}
	else if (input_x == '7') {
		output_x = 6;
	}

	return output_x;
}

int convert_y(char input_y, int output_y)
{
	if (input_y == 'A') {
		output_y = 1;
	}
	else if (input_y == 'B') {
		output_y = 2;
	}
	else if (input_y == 'C') {
		output_y = 3;
	}
	else if (input_y == 'D') {
		output_y = 4;
	}
	else if (input_y == 'E') {
		output_y = 5;
	}
	else if (input_y == 'F') {
		output_y = 6;
	}
	else if (input_y = 'G') {
		output_y = 7;
	}

	return output_y;
}

