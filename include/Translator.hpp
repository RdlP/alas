#ifndef _TRANSLATOR_HEADER
#define _TRANSLATOR_HEADER
#include "Code.hpp"
#include <vector>
#include <iostream>
class Translator
{
public:
	Translator();
	Translator(Code*);
	void translate();

private:
	Code* code;
	std::vector<unsigned char> binaryCode;
	int a = 7;
	int b = 0;
	int c = 1;
	int d = 2;
	int e = 3;
	int h = 4;
	int l = 5;

	int bc = 0;
	int de = 1;
	int hl = 2;
	int sp = 3;

	int nz = 0;
	int z = 1;
	int nc = 2;
	int ca =  3;

	int bit_0 = 0;
	int bit_1 = 1;
	int bit_2 = 2;
	int bit_3 = 3;
	int bit_4 = 4;
	int bit_5 = 5;
	int bit_6 = 6;
	int bit_7 = 7;

};
#endif