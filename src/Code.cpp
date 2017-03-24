#include "Code.hpp"

Code::Code()
{
	
}

void Code::addLine(Line* line)
{
	loc.push_back(line);
}

Line * Code::getLine(int n)
{
	return loc.at(n);
}

int Code::getNumbersOfLines()
{
	return loc.size();
}

std::string Code::toString()
{
	std::string result = "";
	for(std::vector<Line*>::iterator it = loc.begin(); it != loc.end(); it++){
		result += (*it)->toString() + "\n";
	}
	return result;
}