#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "Gaming_field.h"
#include "service.h"
#include "String_functions.h"
#include "Console_visualiser.h"
#include "Competitor.h"
//333
using namespace std;

string Game::start_game() {
	int width, height;
	input_sizeof_field(width, height);

	Gaming_field* field = new Gaming_field(width, height, vis);
	Competitor* first_competitor = nullptr;
	Competitor* second_competitor = nullptr;

	Type_of_turn type_of_turn = input_type_of_turn();
	Type_of_game type_of_game = Competitor::input_type_of_game(first_competitor, second_competitor, vis, type_of_turn);

	for (int cc = 0; !field->is_end(); cc++) {
		if (type_of_game == CvC)
			Sleep(100);
		try {
			if (cc % 2 == 0)
				first_competitor->make_turn(field, Gaming_field::Red);
			else
				second_competitor->make_turn(field, Gaming_field::Black);
		}
		catch (Bad_turn e) { // Неправильный ход
			vis->write(String_functions::char_to_str(e.what()) + "\n", Black, Red);
			cc--;
		}
		catch (Visualiser::Bad_integers_input e) { // не разобрали введенных координат
			vis->write(String_functions::char_to_str(e.what()) + "\n", Black, Red);
			cc--;
		}
	}

	Score score = field->count_score();

	return write_end_information(score);
}

void Game::input_sizeof_field(int& width, int& height) {
	vis->write("Введите размеры поля: ");
	while (1) {
		try {
			vis->input_two_integers(width, height);
			break;
		}
		catch (Visualiser::Bad_integers_input e) {
			vis->write(e.what(), Black, Red);
		}
	}
}

Game::Type_of_turn Game::input_type_of_turn() {
	bool is_mode_defined = false;
	string mode;
	Game::Type_of_turn type;

	vis->write("Как вы будете делать ходы?\na) Перемешение стрелками по полю и установка бочонков клавишей \"Enter\"\nb) Установка бочонков с помощью ввода координат\n");
	do {
		is_mode_defined = true;
		mode = vis->input_string();
		type = Game::get_type_of_turn(mode);

		if (type == Game::ByArrows || type == Game::ByCoordinates) {
			return type;
		}
		else {
			is_mode_defined = false;
			vis->write("Wrong mode. Try again!\n", Black, Red);
		}
	} while (!is_mode_defined);
}

string Game::write_end_information(Game::Score score) {
	if (score.black_player > score.red_player) {
		vis->write("\nBlack player wins\n", Black, Green);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Black player wins\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n";
	}
	else if (score.black_player < score.red_player) {
		vis->write("\nRed player wins\n", Black, Green);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Red player wins\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed_player: " + String_functions::int_to_str(score.red_player) + "\n";
	}
	else {
		vis->write("\nDraw\n", Black, Yellow);
		vis->write("Black: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n");
		return "Draw\nBlack: " + String_functions::int_to_str(score.black_player) + "\nRed: " + String_functions::int_to_str(score.red_player) + "\n";
	}
}

/*void Game::input_type_of_game(Competitor*& first, Competitor*& second) {
	string mode;
	bool is_mode_defined;
	Type_of_game type_of_game;

	vis->write("Выбери два режима:\na) Player vs. Player\nb) Player vs. Computer\nc) Computer vs. Computer\nВведите \'a\', \'b\', \'c\' to choose mode\n");

	do {
		is_mode_defined = true;
		mode = String_functions::input_string();
		type_of_game = get_type_of_game(mode);

		switch (type_of_game) {
		case PvP: // a) PvP
			first = new Player();
			second = new Player();
			break;
		case PvC: // b) PvC
			first = new Player();
			second = new Computer();
			break;
		case CvC: // c) CvC
			first = new Computer();
			second = new Computer();
			vis->write("Игра идет...");
			break;
		default:
			is_mode_defined = false;
			vis->write("Wrong mode. Try again!\n", Black, Red);
		}
	} while (!is_mode_defined);
}*/