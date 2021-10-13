// ћодуль описывает поведение играющей сущности, вне зависимости это компьютер или живой человек

#pragma once

#include <iostream>

#include "Gaming_field.h"
#include "Visualiser.h"

using namespace std;

class Competitor {
protected:
	typedef Gaming_field::Player_type Player_type;
	typedef Game::Type_of_game Type_of_game;
	typedef Game::Type_of_turn Type_of_turn;
	typedef Gaming_field::Cell_state Cell_state;

public:
	virtual void make_turn(Gaming_field*, Player_type) = 0;
	
	static Type_of_game input_type_of_game(Competitor*& first_competitor, Competitor*& second_competitor, Visualiser* vis, Type_of_turn type_of_turn); // осуществл€ет ввод режима игры (PvP, PvC, CvC)
};

class Computer : public Competitor {
private:
	void get_coordinates(Gaming_field*, int& x, int& y, Player_type); // анализирует игровое поле и в x, y записывает координаты наилучшего хода
public:
	void make_turn(Gaming_field*, Player_type);
};

class Player : public Competitor {
private:
	virtual void get_coordinates(int& x, int& y, Player_type, Visualiser*, Gaming_field*) = 0;
public:
	virtual void make_turn(Gaming_field*, Player_type);
};

class Player_ByArrows : public Player {
private:
	enum Move_direction {
		Up,
		Down,
		Right,
		Left,
		Enter
	};

	void get_coordinates(int& x, int& y, Player_type, Visualiser*, Gaming_field*);

	Move_direction get_move();
	bool make_move(int& x, int& y, Move_direction, Gaming_field*, Visualiser* vis); /* јнализирует Move_direction и измен€ет координаты (x, y)
																									(x1, y1) - начальные координаты. ¬озвращает true, если человек нажал enter*/
public:

};

class Player_ByCoordinates : public Player {
private:
	void get_coordinates(int& x, int& y, Player_type, Visualiser*, Gaming_field*);
public:

};