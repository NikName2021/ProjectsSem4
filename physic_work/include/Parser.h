#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include "Quantity.h"
#include "Unit.h"

class Parser {
private:
    std::string input;
    size_t pos;
    std::map<std::string, Unit> units;

    void skipSpaces();
    std::string getNextToken();
    bool peek(char c);

public:
    Parser(const std::string& str, const std::map<std::string, Unit>& unitMap);

    Quantity parse();

    Quantity parseExpression();
    Quantity parseTerm();
    Quantity parseFactor();
};

#endif