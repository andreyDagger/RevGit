#include <iostream>
#include <conio.h>

#include "Competitor.h"

using namespace std;

Game::Type_of_game Competitor::input_type_of_game(Competitor*& first_competitor, Competitor*& second_competitor, Visualiser* vis, Type_of_turn type_of_turn) {
	vis->write("Выбери два режима:\na) Player vs. Player\nb) Player vs. Computer\nc) Computer vs. Computer\nВведите \'a\', \'b\', \'c\' to choose mode\n");

	bool is_mode_defined = false;
	string mode;
	Type_of_game type_of_game;

	do {
		is_mode_defined = true;
		mode = vis->input_string();
		type_of_game = Game::get_type_of_game(mode);

		switch (type_of_game) {
		case Game::PvP: // a) PvP
			if (type_of_turn == Type_of_turn::ByArrows) {
				first_competitor = new Player_ByArrows();
				second_competitor = new Player_ByArrows();
			}
			else if (type_of_turn == Type_of_turn::ByCoordinates) {
				first_competitor = new Player_ByCoordinates();
				second_competitor = new Player_ByCoordinates();
			}
			else {
				vis->write("Unknown type_of_turn in function Competitor::input_type_of_game()\n");
				abort();
			}
			break;
		case Game::PvC: // b) PvC
			if (type_of_turn == Type_of_turn::ByArrows)
				first_competitor = new Player_ByArrows();
			else if (type_of_turn == Type_of_turn::ByCoordinates)
				first_competitor = new Player_ByCoordinates();
			else {
				vis->write("Unknown type_of_turn in function Competitor::input_type_of_game()\n");
				abort();
			}
			second_competitor = new Computer();
			break;
		case Game::CvC: // c) CvC
			first_competitor = new Computer();
			second_competitor = new Computer();
			vis->write("Игра идет...");
			break;
		default:
			is_mode_defined = false;
			vis->write("Wrong mode. Try again!\n", Black, Red);
		}
	} while (!is_mode_defined);

	return type_of_game;
}

void Player::make_turn(Gaming_field* field, Gaming_field::Player_type type) {
	int x = 0, y = 0;
	Visualiser* vis = field->get_visualiser();

	get_coordinates(x, y, type, vis, field);
	field->place_keg_and_revert(x, y, type);
}

void Player_ByArrows::get_coordinates(int& x, int& y, Player_type type, Visualiser* vis, Gaming_field* field) {
	if (type == Gaming_field::Player_type::Black)
		vis->write("Ход черного игрока...");
	else if (type == Gaming_field::Player_type::Red)
		vis->write("Ход красного игрока...");
	else {
		vis->write("Color of player is not defined in function \"Player::make_turn\"\n", Black, Red);
		abort();
	}

	int x1 = 1, y1 = 1, x_prev, y_prev;
	field->find_empty_cell(x1, y1);
	Cell_state prev_keg;

	while (1) {
		prev_keg = field->get_cell_state(x1, y1);
		vis->draw_keg(x1, y1, Gaming_field::getConsoleColor(type));
		x_prev = x1, y_prev = y1;

		Move_direction dir = get_move();
		if (make_move(x1, y1, dir, field, vis)) {
			if (field->get_cell_state(x1, y1) != Gaming_field::Empty) {
				vis->draw_keg(x1, y1, Gaming_field::getConsoleColor(prev_keg));
			}
			break;
		}
		
		if (prev_keg == Gaming_field::Empty)
			vis->erase_cell(x_prev, y_prev);
		else
			vis->draw_keg(x_prev, y_prev, Gaming_field::getConsoleColor(prev_keg));
	}
	x = x1, y = y1;
}

bool Player_ByArrows::make_move(int& x, int& y, Move_direction dir, Gaming_field* field, Visualiser* vis) {
	if (dir == Enter) {
		return true;
	}
	else if (dir == Up) {
		if (y > 1)
			--y;
	}
	else if (dir == Down) {
		if (y < field->get_height())
			++y;
	}
	else if (dir == Left) {
		if (x > 1)
			--x;
	}
	else if (dir == Right) {
		if (x < field->get_width())
			++x;
	}
	else {
		vis->write("Undefined direction in function Player_ByArrows::get_coordinates()", Black, Red);
		abort();
	}
	return false;
}

Player_ByArrows::Move_direction Player_ByArrows::get_move() {
	while (1) {
		int move1 = _getch();
		if (move1 == 13)
			return Enter;
		if (move1 == 224) {
			int move2 = _getch();
			if (move2 == 75)
				return Left;
			else if (move2 == 72)
				return Up;
			else if (move2 == 80)
				return Down;
			else if (move2 == 77)
				return Right;
		}
	}
}

void Player_ByCoordinates::get_coordinates(int& x, int& y, Player_type type, Visualiser* vis, Gaming_field* field) {
	if (type == Gaming_field::Player_type::Black)
		vis->write("Ход черного игрока, введите координаты фишки через пробел: ");
	else if (type == Gaming_field::Player_type::Red)
		vis->write("Ход красного игрока, введите координаты фишки через пробел: ");
	else {
		vis->write("Color of player is not defined in function \"Player::make_turn\"\n", Black, Red);
		abort();
	}

	vis->input_two_integers(x, y);
}

void Computer::make_turn(Gaming_field* field, Gaming_field::Player_type type) {
	int x = 0, y = 0;
	Visualiser* vis = field->get_visualiser();

	if (type == Gaming_field::Player_type::Empty) {
		vis->write("Color of player is not defined in function \"Computer::make_turn\"\n", Black, Red);
		abort();
	}

	get_coordinates(field, x, y, type);
	field->place_keg_and_revert(x, y, type);
}

void Computer::get_coordinates(Gaming_field* field, int& x, int& y, Gaming_field::Player_type type) {
	int max_score = field->count_score(type);
	vector<Gaming_field::keg> reverted_kegs;

	for (int i = 1; i <= field->get_height(); i++)
		for (int j = 1; j <= field->get_width(); j++)
			if (field->get_cell_state(j, i) == Gaming_field::Cell_state::Empty) {
				reverted_kegs = field->place_keg_and_revert(j, i, type);

				int current_score = field->count_score(type);
				if (max_score <= current_score) {
					max_score = current_score;
					x = j, y = i;
				}

				field->redraw_line(reverted_kegs, Gaming_field::getAntiCellState(type));
				field->erase_cell(j, i);
			}
}