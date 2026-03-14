#ifndef UNIT_H
#define UNIT_H

#include "Dimension.h"
#include <string>

class Unit {
private:
    std::string name;
    double factor;
    Dimension dim;
public:
    Unit(std::string n, double f, Dimension d);
    Unit();

    std::string getName() const { return name; }
    double getFactor() const { return factor; }
    Dimension getDimension() const { return dim; }
};

#endif