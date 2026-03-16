#include "../include/Parser.h"
#include <cctype>
#include <stdexcept>

Parser::Parser(const std::string& str, const std::map<std::string, Unit>& unitMap)
    : input(str), pos(0), units(unitMap) {}

void Parser::skipSpaces() {
    while (pos < input.length() && std::isspace(input[pos])) pos++;
}

bool Parser::peek(char c) {
    skipSpaces();
    return pos < input.length() && input[pos] == c;
}

Quantity Parser::parse() {
    return parseExpression();
}

Quantity Parser::parseExpression() {
    Quantity result = parseTerm();
    while (peek('+') || peek('-')) {
        char op = input[pos++];
        Quantity nextTerm = parseTerm();
        if (op == '+') result = result + nextTerm;
        else result = result - nextTerm;
    }
    return result;
}

Quantity Parser::parseTerm() {
    Quantity result = parseFactor();
    while (peek('*') || peek('/')) {
        char op = input[pos++];
        Quantity nextFactor = parseFactor();
        if (op == '*') result = result * nextFactor;
        else result = result / nextFactor;
    }
    return result;
}

Quantity Parser::parseFactor() {
    skipSpaces();

    std::string numStr;
    while (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
        numStr += input[pos++];
    }
    if (numStr.empty()) throw std::runtime_error("Expected a number");
    double val = std::stod(numStr);

    skipSpaces();

    std::string unitStr;
    while (pos < input.length() && std::isalpha(input[pos])) {
        unitStr += input[pos++];
    }

    if (units.find(unitStr) == units.end()) {
        throw std::runtime_error("Unknown unit: " + unitStr);
    }

    return Quantity::fromUnit(val, units[unitStr]);
}