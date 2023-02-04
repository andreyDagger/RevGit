#pragma once

// Some helpful functions to work with strings

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class String_functions {
public:
	static vector<string> split(const string s); // ðàçäåëÿåò ñòðîêó ïî ïðîáåëàì è âîçâðàùàåò vector èç ñëîâ, êîòîðûå áûëè ðàçäåëåíû ïðîáåëàìè
	static string mult(string, int); // óìíîæàåò ñòðîêó íà ÷èñëî n (ïîâòîðÿåò n ðàç)
	static void pchar_copy(char*& dest, const char* src); // safe copying from one char* to another
	static void pchar_copy_dest_null(char*& dest, const char* src); // safe copying from one char* to another if dest = nullptr
	static int strcmp1(char* s1, char* s2); // ñðàâíåíèå ñòðîê ñ ïðèîðèòåòîì íà äëèíó
	static string char_to_str(const char* s); // transforms char to string
	static string int_to_str(int); // transforms int to string
	static string input_string();
};
