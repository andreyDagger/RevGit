#pragma once

#include <iostream>
#include <fstream>

#include "Game.h"
#include "String_functions.h"

using namespace std;

class Online_game : public Game {
public:
	Online_game() {
		Game();
		filename = "source_file.txt";
		source_file.open(filename);
		if (source_file.fail())
			throw Bad_file(filename);
	}

	// Exceptions:

	class Bad_file : public exception {
	public:
		virtual const char* what() {
			return ("Couldn't open file" + filename).c_str();
		}

		Bad_file() : filename("unknown_file") {}
		Bad_file(string fname) : filename(fname) {}
	private:
		string filename;
	};
private:
	ifstream source_file;
	string filename;
};