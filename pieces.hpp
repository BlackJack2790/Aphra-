// Derek Irvin
// Professor Gordon
// Assignment 2: Project Aphra
// Pieces File

#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>


#define WALL 0
#define XWING 1
#define TIEFIGHTER 2
#define DEATHSTAR 3

using namespace std;

// Piece Owner - Similar to that of how Chess has a black and white players we have the player and aphra
enum PieceOwner
{
	Player, Aphra
};

// Types of Pieces
// 2 walls per player
// 4 x wings per player
// 4 tie fighters per player
// one deathstar 

// Enumeration of the types of pieces. 
// 0 - wall, 1 - xwing, 2 - tiefighter, 3- Deathstar
enum PieceType
{
	wall, xwing, tiefighter, deathstar
};

class Piece {
public:

	// Polymorphism since all the pieces will have different shapes and move structures.  
	virtual void print() = 0;
	// Pieces have an owner and a type
	// May add location before tournament based on time to make it simpler to find pieces. 
	// getters 
	PieceOwner get_owner()
	{
		return owner;
	}

	PieceType get_type()
	{
		return type;
	}

	static const int value;
	
protected:
	PieceType type;
	PieceOwner owner;
};

class Wall : public Piece {
public:
	Wall(PieceOwner owner) {
		this->type = wall;
		this->owner = owner;
	}
	// Walls have a low value to insist on NOT going for these moves. 
	static const int value = 50;
	void print() {
		if (get_owner() == Player)
		{
			cout << " + ";
		}
		else if (get_owner() == Aphra) {
			cout << " ~ ";
		}
	}
};

class DeathStar : public Piece {
public:
	DeathStar(PieceOwner owner)
	{
		this->type = deathstar;
		this->owner = owner;
	}
	// Since deathstar is the prize to win other than removing the tie fighters and xwings the value for the deathstar is higher than all other pieces combined. 
	static const int value = 5000;
	void print() {
		if (get_owner() == Player) 
		{
			cout << " @ ";
		}
		else if (get_owner() == Aphra)
		{
			cout << " * ";
		}
	}
};

class XWing : public Piece {
public:
	XWing(PieceOwner owner)
	{
		this->type = xwing;
		this->owner = owner;
	}

	static const int value = 500; // single tie fighters and xwings are worth 500 each adding up to almost the same value as a deathstar
	void print() {
		if (get_owner() == Player) {
			cout << " x ";
		}
		else if (get_owner() == Aphra)
		{
			cout << " X ";
		}
	}
};

class TieFighter : public Piece
{
public:
	TieFighter(PieceOwner owner)
	{
		this->type = tiefighter;
		this->owner = owner;
	}

	static const int value = 500;
	void print() {
		if (get_owner() == Player) {
			cout << " t ";
		}
		else if (get_owner() == Aphra)
		{
			cout << " T ";
		}
	}
};

#endif
