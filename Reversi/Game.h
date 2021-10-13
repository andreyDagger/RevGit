#pragma once

#include <iostream>
#include "Console_visualiser.h"

using namespace std;

class Game {
public:
	Game() {
		vis = new Console_visualiser();
	}

	enum Type_of_game {
		PvP,
		PvC,
		CvC,
		None
	};
	static inline Type_of_game get_type_of_game(string s) {
		if (s == "a")
			return PvP;
		else if (s == "b")
			return PvC;
		else if (s == "c")
			return CvC;
		else
			return Type_of_game::None;
	}

	enum Type_of_turn {
		ByArrows,
		ByCoordinates,
	};
	static inline Type_of_turn get_type_of_turn(string s) {
		if (s == "a")
			return ByArrows;
		else if (s == "b")
			return ByCoordinates;
		else
			throw;
	}

	typedef struct Score {
		int red_player;
		int black_player;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	string start_game(); // начинает игру с полем с заданными размерами, возвращает сообщение о конце игры
	///
	/////////////////////////

	// Исключения:

	class Bad_turn : public exception {
	private:
		string error_message;
	public:
		Bad_turn(string s) : error_message(s) {}

		const char* what() {
			return error_message.c_str();
		}
	};
	
	Visualiser* vis;
private:

	void input_sizeof_field(int& w, int& h); // осуществляет ввод размеров поля
	Type_of_turn input_type_of_turn(); // осуществляет ввод режима хода
	string write_end_information(Score); // выводит на экран информацию об окончании партии*/

};