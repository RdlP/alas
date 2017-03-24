#include "Translator.hpp"

Translator::Translator()
{
	
}

Translator::Translator(Code* code): code(code)
{
	
}

void Translator::translate()
{
	for(int i = 0; i < code->getNumbersOfLines(); i++){
		Line *line = code->getLine(i);
		int binary = 0;
		std::string command = line->getCommand();
		if (command == "LD"){
			binary = 0x06;
			if (line->getOP1() == "a"){
				binary |= a << 3;
			}else if (line->getOP1() == "b"){
				binary |= b << 3;
			}else if (line->getOP1() == "c"){
				binary |= c << 3;
			}else if (line->getOP1() == "d"){
				binary |= d << 3;
			}else if (line->getOP1() == "e"){
				binary |= e << 3;
			}else if (line->getOP1() == "h"){
				binary |= h << 3;
			}else if (line->getOP1() == "l"){
				binary |= l << 3;
			}
			binaryCode.push_back(binary);
			binaryCode.push_back(std::stoul(line->getOP2(), nullptr, 16));
		}else if (command == "DEC"){
			binary = 0x05;
			if (line->getOP1() == "a"){
				binary |= a << 3;
			}else if (line->getOP1() == "b"){
				binary |= b << 3;
			}else if (line->getOP1() == "c"){
				binary |= c << 3;
			}else if (line->getOP1() == "d"){
				binary |= d << 3;
			}else if (line->getOP1() == "e"){
				binary |= e << 3;
			}else if (line->getOP1() == "h"){
				binary |= h << 3;
			}else if (line->getOP1() == "l"){
				binary |= l << 3;
			}
			binaryCode.push_back(binary);
		}else if (command == "ADD"){
			binary = 0x80;
			if (line->getOP2() == "a"){
				binary |= a;
			}else if (line->getOP2() == "b"){
				binary |= b;
			}else if (line->getOP2() == "c"){
				binary |= c;
			}else if (line->getOP2() == "d"){
				binary |= d;
			}else if (line->getOP2() == "e"){
				binary |= e;
			}else if (line->getOP2() == "h"){
				binary |= h;
			}else if (line->getOP2() == "l"){
				binary |= l;
			}
		}else if (command == "JRNZ"){
			binary = 0xC2;
			int dir = std::stoul(line->getOP1(), nullptr, 16);
			binaryCode.push_back(dir&0xFF);
			binaryCode.push_back((dir>>8)&0xFF);
		}else if (command == "BIT"){
			binaryCode.push_back(0xCB);
			binary = 0x40;
			if (line->getOP2() == "a"){
				binary |= a;
			}else if (line->getOP2() == "b"){
				binary |= b;
			}else if (line->getOP2() == "c"){
				binary |= c;
			}else if (line->getOP2() == "d"){
				binary |= d;
			}else if (line->getOP2() == "e"){
				binary |= e;
			}else if (line->getOP2() == "h"){
				binary |= h;
			}else if (line->getOP2() == "l"){
				binary |= l;
			}

			if (line->getOP1() == "0"){
				binary |= bit_0 << 3;
			}else if (line->getOP1() == "1"){
				binary |= bit_1 << 3;
			}else if (line->getOP1() == "2"){
				binary |= bit_2 << 3;
			}else if (line->getOP1() == "3"){
				binary |= bit_3 << 3;
			}else if (line->getOP1() == "4"){
				binary |= bit_4 << 3;
			}else if (line->getOP1() == "5"){
				binary |= bit_5 << 3;
			}else if (line->getOP1() == "6"){
				binary |= bit_6 << 3;
			}else if (line->getOP1() == "7"){
				binary |= bit_7 << 3;
			}
			binaryCode.push_back(binary);
		}else if (command == "NOP"){
			binaryCode.push_back(0x00);
		}else if (command == "JP"){
			binaryCode.push_back(0xC3);
			int dir = std::stoul(line->getOP1(), nullptr, 16);
			binaryCode.push_back(dir&0xFF);
			binaryCode.push_back((dir>>8)&0xFF);
		}
	}
	std::cout << "=============" << std::endl;
	std::cout << "=Binary code=" << std::endl;
	std::cout << "=============" << std::endl;
	for (int i = 0; i < binaryCode.size()-1; i++){
		printf("0x%02X ", binaryCode.at(i));
		if (i != 0 && i % 16 == 0){
			printf("\n");
		}
	}
	printf("\n");
}