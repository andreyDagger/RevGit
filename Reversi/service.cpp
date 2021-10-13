#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sys\stat.h>
#include "service.h"

using namespace std;

void set_global_var(int value) {
    GLOBAL_VARIABLE = value;
}

int get_global_var() {
    return GLOBAL_VARIABLE;
}

void SetConsoleColor(ConsoleColor color_back, ConsoleColor color_text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((color_back << 4) | color_text));
}

void print_color(const char* s, ConsoleColor color_back, ConsoleColor color_text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((color_back << 4) | color_text));
    cout << s;
    SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
}

void print_color_endl(const char* s, ConsoleColor color_back, ConsoleColor color_text) {
    print_color(s, color_back, color_text);
    cout << endl;
}

void SetConsoleCursorPos(int x, int y) {
    COORD position;										// ���������� ����������� ���������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// ��������� ����������� ���������� ������������ ������
    position.X = x;									// ��������� ���������� X
    position.Y = y;									// ��������� ���������� Y
    SetConsoleCursorPosition(hConsole, position);
}

void arrange(int& n, int& m) {
    if (n > m)
        swap(n, m);
}