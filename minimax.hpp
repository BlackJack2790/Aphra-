
#ifndef TCHESS_ALGORITHMS_HPP
#define TCHESS_ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "board.hpp"
#include "pieces.hpp"

Board* ABMinMax(Board* board, short int depth_limit);
Board* ABMaxMove(Board* board, short int depth_limit, short int depth, int a, int b);
Board* ABMinMove(Board* board, short int depth_limit, short int depth, int a, int b);


Board* ABMinMax(Board* board, short int limit)
{
	return ABMaxMove(board, limit, 1, 0, 0); // (state of board, depth, current depth, alpha, beta)
}

Board* ABMaxMove(Board* board, short int limit, short int depth, int a, int b)
{
	vector<Board*> *moves;	// List of moves
	Board* best_move = NULL; // Best Move
	Board* best_real_move = NULL; // Final answer // Need to send this back up to the main function to print out to the user. 
	Board* move = NULL; // current move
	int alpha = a, beta = b; // Alpha beta values. 

	// Limit of ply met in the beginning
	if (depth >= limit)
	{
		return board;
	}
	else
	{
		moves = board->list_all_moves(); // Find list of all moves that can be done on the pieces. 
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) //Vector Iterator through the moves beginning to end. 
		{
			move = ABMinMove(*it, limit, depth+1, alpha, beta); // Search to the next depth
			if (best_move == NULL || move->evaluate(Aphra) > best_move->evaluate(Aphra)) {
				best_move = move;
				best_real_move = *it;
				alpha = move->evaluate(Aphra);
			}
			if (beta < alpha) {
				return best_real_move;
			}
		}
		return best_real_move;
	}
}

Board* ABMinMove(Board* board, short int limit, short int depth, int a, int b) {
	vector<Board*> *moves;
	Board* best_move = NULL;
	Board* best_real_move = NULL;
	Board* move = NULL;
	int alpha = a;
	int beta = b;

	if (depth >= limit) {//if depth limit is reached
		return board;
	}
	else 
	{
		moves = board->list_all_moves();
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) {
			move = ABMaxMove(*it, limit, depth+1, alpha, beta);
			if (best_move == NULL || move->evaluate(Player) > best_move->evaluate(Player)) 
			{
				best_move = move;
				best_real_move = *it;
				beta = move->evaluate(Player);
			}
			if (beta < alpha) {
				return best_real_move;
			}
		}
		return best_real_move;
	}
}

#endif