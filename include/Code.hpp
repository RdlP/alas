#ifndef _CODE_HEADER
#define _CODE_HEADER
#include <vector>
#include "Line.hpp"
#include <string>
#include <map>

class Code
{
public:
	Code();
	void addLine(Line* line);
	Line* getLine(int n);
	int getNumbersOfLines();
	std::string toString();
private:
	std::vector<Line*> loc;
};
#endif