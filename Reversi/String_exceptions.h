#pragma once

#include <iostream>

using namespace std;

class CharOverflow : public exception { // Рaзмер char[] массива слишком маленький
public:
	CharOverflow() {
	}
};

class CharNullptr : public exception { // char* оказался nullptr
public:
	CharNullptr() {
	}
};