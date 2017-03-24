#ifndef _LINE_HEADER
#define _LINE_HEADER
#include <vector>
#include <string>
#include <sstream> 
#include <iostream>
#include <map>
#include <stdlib.h>
#include <algorithm>

class Line
{

	public:

		enum OPType{
			REGISTER,
			INMEDIATE_8BITS,
			INMEDIATE_16BITS,
			REGISTER_COMPOSED
		};
		Line(std::string, std::string, std::string);
		Line(std::string, std::string);
		std::string getCommand();
		std::string getOP1();
		std::string getOP2();
		void setOP1Type(OPType type);
		void setOP2Type(OPType type);
		OPType getOP1Type();
		OPType getOP2Type();

		void setOP1(std::string);
		void setOP2(std::string);
		static Line *lineFactory(std::string, std::map<std::string, int> *symbolTable, int *nline);
		std::string toString();
		static bool isIntegerNumber(const std::string& s);
		static std::string toLowerCase(std::string);
		static bool startsWithIgnoreCase(std::string, std::string );
		

	private:
		std::string command;
		std::string op1;
		std::string op2;
		OPType op1Type;
		OPType op2Type;
	
};
#endif