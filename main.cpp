#include "Parser.hpp"
#include "Code.hpp"
#include "Translator.hpp"

using namespace std; 

int main(int argc, char* argv[]) 
{
    Parser *parser = new Parser("./test");
    parser->parse();
    Code *code = parser->getCode();
    Translator *translator = new Translator(code);
    translator->translate();
  return 0;
}
