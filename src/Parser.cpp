#include "Parser.hpp"

Parser::Parser(std::string filename): filename(filename)
{
	code = new Code();
}

void Parser::parse()
{
	firstPass();
	finalPass();
}

Code * Parser::getCode()
{
	return code;
}

void Parser::firstPass()
{
	std::cout << "===========================" << std::endl;
	std::cout << "=Parsing file (First pass)=" << std::endl;
	std::cout << "===========================" << std::endl;
	std::ifstream infile(filename);
	std::string line;
	int nByte = 0;
	while (std::getline(infile, line))
	{
		Line *l = Line::lineFactory(line, &symbolTable, &nByte);
		if (l != nullptr){
			code->addLine(l);
			nByte++;
		}
	    /*std::istringstream iss(line);
	    int a, b;
	    if (!(iss >> a >> b)) { break; } // error

	    // process pair (a,b)*/

	}

	std::cout << "Result of First Pass" << std::endl;
	std::cout << code->toString();
	std::cout << "SYMBOL TABLE" << std::endl;

	for (std::map<std::string, int>::iterator it = symbolTable.begin(); it != symbolTable.end(); it++){
		std::cout << it->first << " => " << it->second << '\n';
	}
}

std::string Parser::intToHex(int n, unsigned char bits){
	std::stringstream stream;
	if (bits == 16){
  		stream << "0x" 
         << std::setfill ('0') << std::setw(4) 
         << std::hex << n;
    }else if (bits == 8){
    	stream << "0x" 
         << std::setfill ('0') << std::setw(2) 
         << std::hex << n;
    }
  	return stream.str();
}

void Parser::finalPass()
{
	std::cout << "================================" << std::endl;
	std::cout << "=Resolving symbols (Final Pass)=" << std::endl;
	std::cout << "================================" << std::endl;
	for(int i = 0; i < code->getNumbersOfLines(); i++){
		Line *line = code->getLine(i);
		for (std::map<std::string, int>::iterator it = symbolTable.begin(); it != symbolTable.end(); it++){
			std::string symbol = it->first.substr(0, it->first.length()-1);
			if (symbol == line->getOP1()){
				if (it->second < 255){
					line->setOP1(intToHex(it->second, 8));
				}else{
					line->setOP1(intToHex(it->second, 16));
				}
				
			}
			if (symbol == line->getOP2()){
				if (it->second < 255){
					line->setOP1(intToHex(it->second, 8));
				}else{
					line->setOP2(intToHex(it->second, 16));
				}
			}
			//std::cout << it->first << " => " << it->second << '\n';
		}
	}

	std::cout << "Result of Final Pass" << std::endl;
	std::cout << code->toString();
}