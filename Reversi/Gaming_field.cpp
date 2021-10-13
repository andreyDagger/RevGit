#include <iostream>

#include "Gaming_field.h"
#include "Visualiser.h"
#include "Console_visualiser.h"
#include "service.h"

using namespace std;

Gaming_field::Gaming_field(int width, int height, Visualiser* v) : width(width), height(height) {
	if (width < 2 || height < 2)
		throw Gaming_field::Bad_field_size(width, height);
	field = new Cell_state * [height];
	vis = new Console_visualiser();
	for (int i = 0; i < height; i++) {
		field[i] = new Cell_state[width];
		for (int j = 0; j < width; j++)
			field[i][j] = Empty;
	}

	field[height / 2 - 1][width / 2 - 1] = Black;
	field[height / 2][width / 2] = Black;
	field[height / 2][width / 2 - 1] = Red;
	field[height / 2 - 1][width / 2] = Red;

	vis = v;
	vis->draw_field(width, height);
	vis->draw_keg(width / 2, height / 2, ConsoleColor::Black);
	vis->draw_keg(width / 2 + 1, height / 2 + 1, ConsoleColor::Black);
	vis->draw_keg(width / 2, height / 2 + 1, ConsoleColor::Red);
	vis->draw_keg(width / 2 + 1, height / 2, ConsoleColor::Red);

}

Gaming_field::Gaming_field(Visualiser* v) {

}

Game::Score Gaming_field::count_score() {
	Game::Score score;
	score.black_player = 0;
	score.red_player = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == Cell_state::Black)
				score.black_player++;
			else if (field[i][j] == Cell_state::Red)
				score.red_player++;
		}
	}

	return score;
}

void Gaming_field::find_empty_cell(int& x, int& y) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == Empty) {
				x = j + 1;
				y = i + 1;
				return;
			}
		}
	}
	vis->write("Function Gaming_field::find_empty_cell() couldn't find empty_cell");
	abort();
}

int Gaming_field::count_score(Player_type type) {
	if (type == Black)
		return count_black_score();
	else if (type == Red)
		return count_red_score();
	else {
		vis->write("Type of Player is not defined in function Gaming_field::count_score\n", ConsoleColor::Black, ConsoleColor::Red);
		abort();
	}
}

int Gaming_field::count_red_score() {
	return count_score().red_player;
}

int Gaming_field::count_black_score() {
	return count_score().black_player;
}

bool Gaming_field::is_end() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] == Cell_state::Empty)
				return false;
		}
	}
	return true;
}

vector<Gaming_field::keg> Gaming_field::place_keg_and_revert(int x, int y, Cell_state keg_type) {

	if (x <= 0 || x > width || y <= 0 || y > height)								//----
		throw Game::Bad_turn("“ак нельз€ ходить, вы вышли за рамки пол€");			//   |---> Ёто проверка на правильность хода
	if (field[y - 1][x - 1] != Empty)											  	//   |
		throw Game::Bad_turn("“ак нельз€ ходить, в этой клетке уже стоит фишка"); 	//----																																	  

	if (keg_type != Cell_state::Black && keg_type != Cell_state::Red) {
		vis->write("Unknown color (type) of keg in function place_keg()\n", ConsoleColor::Black, ConsoleColor::Red);
		abort();
	}
	else
		place_keg(x, y, keg_type);
	
	return revert_kegs(x, y, keg_type);
}

void Gaming_field::place_keg(int x, int y, Cell_state keg_type) {
	field[y - 1][x - 1] = keg_type;
	vis->draw_keg(x, y, getConsoleColor(keg_type));
}

vector<Gaming_field::keg> Gaming_field::redraw_line(int x1, int y1, int x2, int y2, Cell_state keg_type, Direction dir) {
	vector<Gaming_field::keg> res;

	switch (dir) {
	case Up: case Down:
		arrange(y1, y2);
		for (int i = y1 - 1; i < y2; i++) {
			place_keg(x1, i + 1, keg_type);
			if (i != y1 - 1 && i != y2 - 1)
				res.push_back({x1, i + 1});
		}
		break;
	case Left: case Right:
		arrange(x1, x2);
		for (int i = x1 - 1; i < x2; i++) {
			place_keg(i + 1, y1, keg_type);
			if (i != x1 - 1 && i != x2 - 1)
				res.push_back({ i + 1, y1 });
		}
		break;
	case Up_left: case Down_right:
		arrange(x1, x2);
		arrange(y1, y2);
		for (int i = x1 - 1, j = y1 - 1; i < x2 && j < y2; i++, j++) {
			place_keg(i + 1, j + 1, keg_type);
			if (i != x1 - 1 && i != x2 - 1)
				res.push_back({ i + 1, j + 1 });
		}
		break;
	case Up_right: case Down_left:
		arrange(x1, x2);
		arrange(y1, y2);
		for (int i = x1 - 1, j = y2 - 1; i <= x2 && j >= y1; i++, j--) {
			place_keg(i + 1, j + 1, keg_type);
			if (i != x1 - 1 && i != x2)
				res.push_back({ i + 1, j + 1 });
		}
		break;
	default:
		vis->write("Unknown \"Direction\" in function \"Gaming_field::redraw_line()\"\n", ConsoleColor::Black, ConsoleColor::Red);
		abort();
	}

	return res;
}

void Gaming_field::redraw_line(vector<keg> kegs, Cell_state keg_type) {
	for (int i = 0; i < kegs.size(); i++) {
		place_keg(kegs[i].first, kegs[i].second, keg_type);
	}
}

void Gaming_field::erase_cell(int x, int y) {
	field[y - 1][x - 1] = Empty;
	vis->erase_cell(x, y);
}