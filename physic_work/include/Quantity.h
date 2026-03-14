#ifndef QUANTITY_H
#define QUANTITY_H

#include "Dimension.h"
#include "Unit.h"

class Quantity {
private:
    double valueSI;
    Dimension dim;
public:
    Quantity(double valSI, Dimension d);

    static Quantity fromUnit(double value, const Unit& unit);

    Quantity operator+(const Quantity& other) const;
    Quantity operator-(const Quantity& other) const;
    Quantity operator*(const Quantity& other) const;
    Quantity operator/(const Quantity& other) const;

    void printSI() const;
    void printAs(const Unit& unit) const;
};

#endif