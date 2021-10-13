#pragma once

#include <iostream>

#include "Game.h"
#include "service.h"
#include "Visualiser.h"
#include "String_functions.h"

using namespace std;

class Gaming_field {
public:

	enum Cell_state {
		Empty,
		Black,
		Red
	};

	static inline ConsoleColor getConsoleColor(Cell_state keg_type) {
		if (keg_type == Black)
			return ConsoleColor::Black;
		else if (keg_type == Red)
			return ConsoleColor::Red;
		else
			throw;
	}

	static inline Cell_state getAntiCellState(Cell_state keg_type) {
		if (keg_type == Cell_state::Black)
			return Cell_state::Red;
		else if (keg_type == Cell_state::Red)
			return Cell_state::Black;
		else {
			cout << "getAntiCellState\n"; // эта запись должна идти в лог (надо переписать)
			abort();
		}
	}

	enum Direction {
		Up,
		Down,
		Right,
		Left,
		Up_left,
		Up_right,
		Down_left,
		Down_right
	};

	typedef Gaming_field::Cell_state Player_type; // чтобы знать кто ходит черный или красный
	typedef pair<int, int> keg; // keg - координаты бочонка

	Gaming_field(Visualiser*); // создает поле 8x8
	Gaming_field(int, int, Visualiser*); // создает поле с заданными размерами

	vector<keg> place_keg_and_revert(int x, int y, Cell_state keg_type); /* ставит фишку в заданные координаты с заданным цветом (типом)
																		 и провер€ет, надо ли развернуть какие-нибудь фишки.
																		 ¬озвращает список бочонков, которые функци€ перевернула*/

	Game::Score count_score(); // подсчитывает кол-во очков красного и черного игроков
	int count_score(Player_type); // подсчитывает кол-во очков игрока определенного типа (красного либо синего)

	bool is_end(); // сообщает закончилась ли игра, или нет

	void initialize(); // чистит поле и создает его заново с размерами 8x8
	void initialize(int, int); // чистит поле и создает его заново с заданными размерами

	inline int get_height() const { return height; }
	inline int get_width() const { return width; }
	inline Cell_state get_cell_state(int x, int y) const { return field[y - 1][x - 1]; }
	inline Visualiser* get_visualiser() const { return vis; }

	void erase_cell(int x, int y); // стирает фишку с координатами x, y

	vector<keg> redraw_line(int x_1, int y_1, int x_2, int y_2, Cell_state col, Direction dir);
	void redraw_line(vector<keg> kegs, Cell_state);

	void find_empty_cell(int& x, int& y); // ищет пустую клетку и записывает еЄ координаты в (x, y)

	// »сключени€:
	class Bad_field_size : public exception {
	private:
		int width, height;
		string error_message;
	public:
		Bad_field_size(int w, int h) : width(w), height(h) {}

		const char* what() {
			error_message = "Ќеправильный размер пол€, оба параметра (" + String_functions::int_to_str(width) + ", " + String_functions::int_to_str(height) + ") не должны быть меньше 2-ух";
			return error_message.c_str();
		}
	};

private:
	Cell_state** field;
	int width, height;

	Visualiser* vis;

	vector<keg> revert_kegs(int x, int y, Cell_state keg_type); // когда игрок ставит фишку надо какие-то фишки перевернуть, чем эта ф-и€ и занимаетс€
	
	bool find_up_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет сверху фишку такого же цвета (типа)
	bool find_down_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет снизу фишку такого же цвета (типа)
	bool find_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет слева фишку такого же цвета (типа)
	bool find_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет справа фишку такого же цвета (типа)
	bool find_up_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет по диагонали сверху слева фишку такого же цвета (типа)
	bool find_up_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет по диагонали сверху справа фишку такого же цвета (типа)
	bool find_down_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет по диагонали снизу справа фишку такого же цвета (типа)
	bool find_down_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // »щет по диагонали снизу слева фишку такого же цвета (типа)
	//  ќќ–ƒ»Ќј“џ Ќј…ƒ≈ЌЌќ… ‘»Ў » «јѕ»—џ¬јё“—я ¬ x_1 и y_1, в случае неудачи x_1 = nullptr и y_1 = nullptr
	
	void place_keg(int x, int y, Cell_state keg_type); // просто ставит фишку в заданные координаты

	int count_red_score();
	int count_black_score();
};