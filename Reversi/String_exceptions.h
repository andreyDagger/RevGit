#pragma once

#include <iostream>

using namespace std;

class CharOverflow : public exception { // �a���� char[] ������� ������� ���������
public:
	CharOverflow() {
	}
};

class CharNullptr : public exception { // char* �������� nullptr
public:
	CharNullptr() {
	}
};