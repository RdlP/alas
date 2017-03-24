#ifndef _PARSER_HEADER
#define _PARSER_HEADER
#include <string>
#include <fstream>
#include "Code.hpp"
#include "Line.hpp"
#include <iostream>
#include <map>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

class Parser
{
public:
	Parser(std::string);
	void firstPass();
	void finalPass();
	void parse();
	Code* getCode();
	std::string intToHex(int n, unsigned char bits);

private:
	std::string filename;
	Code *code;
	std::map<std::string, int> symbolTable;
};

#endif