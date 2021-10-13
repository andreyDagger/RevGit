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
			cout << "getAntiCellState\n"; // ��� ������ ������ ���� � ��� (���� ����������)
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

	typedef Gaming_field::Cell_state Player_type; // ����� ����� ��� ����� ������ ��� �������
	typedef pair<int, int> keg; // keg - ���������� �������

	Gaming_field(Visualiser*); // ������� ���� 8x8
	Gaming_field(int, int, Visualiser*); // ������� ���� � ��������� ���������

	vector<keg> place_keg_and_revert(int x, int y, Cell_state keg_type); /* ������ ����� � �������� ���������� � �������� ������ (�����)
																		 � ���������, ���� �� ���������� �����-������ �����.
																		 ���������� ������ ��������, ������� ������� �����������*/

	Game::Score count_score(); // ������������ ���-�� ����� �������� � ������� �������
	int count_score(Player_type); // ������������ ���-�� ����� ������ ������������� ���� (�������� ���� ������)

	bool is_end(); // �������� ����������� �� ����, ��� ���

	void initialize(); // ������ ���� � ������� ��� ������ � ��������� 8x8
	void initialize(int, int); // ������ ���� � ������� ��� ������ � ��������� ���������

	inline int get_height() const { return height; }
	inline int get_width() const { return width; }
	inline Cell_state get_cell_state(int x, int y) const { return field[y - 1][x - 1]; }
	inline Visualiser* get_visualiser() const { return vis; }

	void erase_cell(int x, int y); // ������� ����� � ������������ x, y

	vector<keg> redraw_line(int x_1, int y_1, int x_2, int y_2, Cell_state col, Direction dir);
	void redraw_line(vector<keg> kegs, Cell_state);

	void find_empty_cell(int& x, int& y); // ���� ������ ������ � ���������� � ���������� � (x, y)

	// ����������:
	class Bad_field_size : public exception {
	private:
		int width, height;
		string error_message;
	public:
		Bad_field_size(int w, int h) : width(w), height(h) {}

		const char* what() {
			error_message = "������������ ������ ����, ��� ��������� (" + String_functions::int_to_str(width) + ", " + String_functions::int_to_str(height) + ") �� ������ ���� ������ 2-��";
			return error_message.c_str();
		}
	};

private:
	Cell_state** field;
	int width, height;

	Visualiser* vis;

	vector<keg> revert_kegs(int x, int y, Cell_state keg_type); // ����� ����� ������ ����� ���� �����-�� ����� �����������, ��� ��� �-�� � ����������
	
	bool find_up_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� ������ ����� ������ �� ����� (����)
	bool find_down_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� ����� ����� ������ �� ����� (����)
	bool find_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� ����� ����� ������ �� ����� (����)
	bool find_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� ������ ����� ������ �� ����� (����)
	bool find_up_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� �� ��������� ������ ����� ����� ������ �� ����� (����)
	bool find_up_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� �� ��������� ������ ������ ����� ������ �� ����� (����)
	bool find_down_right_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� �� ��������� ����� ������ ����� ������ �� ����� (����)
	bool find_down_left_same_color(int x, int y, Cell_state keg_type, int* x_1, int* y_1); // ���� �� ��������� ����� ����� ����� ������ �� ����� (����)
	// ���������� ��������� ����� ������������ � x_1 � y_1, � ������ ������� x_1 = nullptr � y_1 = nullptr
	
	void place_keg(int x, int y, Cell_state keg_type); // ������ ������ ����� � �������� ����������

	int count_red_score();
	int count_black_score();
};