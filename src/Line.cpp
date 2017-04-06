#include "Line.hpp"

Line::Line(std::string command, std::string op1, std::string op2): command(command), op1(op1), op2(op2)
{
	
}

Line::Line(std::string command, std::string op1): command(command), op1(op1)
{
	
}

bool Line::isIntegerNumber(const std::string& s)
{
	if (s.empty()){
		return false;
	}
	if (s.at(0) != '+' && s.at(0) != '-' && !std::isdigit(s.at(0))){
		return false;
	}
    std::string::const_iterator it = s.begin()+1;
    while (it != s.end() && std::isdigit(*it)) ++it;
    return it == s.end();
}

bool Line::startsWithIgnoreCase(std::string source, std::string find)
{
	std::string c = toLowerCase(source);
	std::string f = toLowerCase(find);
	for (int i = 0; i < find.length(); i++){
		if (i >= c.length()){
			return false;
		}
		if (c.at(i) != f.at(i)){
			return false;
		}
	}
	return true;
}

std::string Line::toLowerCase(std::string str)
{
	std::string data = str;
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

Line *Line::lineFactory(std::string line, std::map<std::string, int> *symbolTable, int *nByte)
{
	std::stringstream  stream(line);
	std::string  word;
	stream >> word;

	std::string c = word;
	if (c == "" || c.at(0) == ';'){
		return nullptr;
	}
	if (c.find(":") != std::string::npos) {
	    symbolTable->insert(std::pair<std::string,int>(c, *nByte));
	    return nullptr;
	}
	int length = c.length();
	bool findingFirstOP = true;
	bool gettingFirstOP = false;
	bool findingSecondOP = false;
	bool gettingSecondOP = false;
	std::string o1 = "";
	std::string o2 = "";
	int realLength = line.find(c);
	if (realLength == std::string::npos){
		return nullptr;
	}
	length += realLength;
	//std::cout << "lengt: " << length << std::endl;
	for (int i = length; i < line.length(); i++){
		//std::cout << "char " << line.at(i) << std::endl;
		if (line.at(i) == ';'){
				break;
			}
		if (findingFirstOP){
			//std::cout << "findingFirstOP" << std::endl;
			if (line.at(i) == ' ' || line.at(i) == '\t'){
				continue;
			}else{
				findingFirstOP = false;
				gettingFirstOP = true;
				findingSecondOP = false;
				gettingSecondOP = false;
			}
		}
		if (gettingFirstOP){
			//std::cout << "gettingFirstOP" << std::endl;
			if (line.at(i) != ' ' && line.at(i) != ','){
				o1 += line.at(i);
				continue;
			}else{
				findingFirstOP = false;
				gettingFirstOP = false;
				findingSecondOP = true;
				gettingSecondOP = false;
			}
		}
		if (findingSecondOP){
			//std::cout << "findingSecondOP" << std::endl;
			if (line.at(i) == ' ' || line.at(i) == '\t' || line.at(i) == ','){
				continue;
			}else{
				findingFirstOP = false;
				gettingFirstOP = false;
				findingSecondOP = false;
				gettingSecondOP = true;
			}
		}
		if (gettingSecondOP){
			//std::cout << "gettingSecondOP" << std::endl;
			o2 += line.at(i);
		}
	}
	/*stream >> word;
	
	if (stream >> word){
		o2 = word;
	}*/

	OPType op1Type, op2Type;
	
	std::string commandLowerCase = toLowerCase(c);
	if (commandLowerCase == "rlc" || commandLowerCase == "rrc" || commandLowerCase == "rl" ||
		commandLowerCase == "rr" || commandLowerCase == "sla" || commandLowerCase == "sra" ||
		commandLowerCase == "swap" || commandLowerCase == "srl" || commandLowerCase == "bit" ||
		commandLowerCase == "res" || commandLowerCase == "set"){
		(*nByte)++;
	}else{
		if ((commandLowerCase.at(0) == 'j' && commandLowerCase.at(1) == 'p') || commandLowerCase == "jp"){
			*nByte += 2;
			if (isIntegerNumber(o1)){
				op1Type = INMEDIATE_16BITS;
			}else{
				if (o1.length() > 1){
					op1Type = REGISTER_COMPOSED;
				}else{
					op1Type = REGISTER;
				}
			}
		}else{
			if (isIntegerNumber(o1)){
				int tmp = atoi(o1.c_str());
				if (tmp < 256){
					(*nByte)++;
				}else if (tmp < 65536){
					*nByte += 2;
				}
				op1Type = INMEDIATE_8BITS;
			}else{
				op1Type = REGISTER;
			}
			if (isIntegerNumber(o2)){
				int tmp = atoi(o2.c_str());
				if (tmp < 256){
					(*nByte)++;
				}else if (tmp < 65536){
					*nByte += 2;
				}
				op2Type = INMEDIATE_8BITS;
			}else{
				op2Type = REGISTER;
			}
		}
	}
	Line *l = new Line(c, o1, o2);
	l->setOP1Type(op1Type);
	l->setOP2Type(op2Type);
	return l;
}

std::string Line::getCommand()
{
	return command;
}

std::string Line::getOP1()
{
	return op1;
}

std::string Line::getOP2()
{
	return op2;
}

void Line::setOP1(std::string newOP1)
{
	op1 = newOP1;
}

void Line::setOP2(std::string newOP2)
{
	op2 = newOP2;
}

void Line::setOP1Type(OPType type)
{
	op1Type = type;
}

void Line::setOP2Type(OPType type)
{
	op2Type = type;
}

Line::OPType Line::getOP1Type()
{
	return op1Type;
}

Line::OPType Line::getOP2Type()
{
	return op1Type;
}

std::string Line::toString()
{
	std::string result = "Command: " + command + " op1: " + op1 + " op2: " + op2;
	return result;
}
