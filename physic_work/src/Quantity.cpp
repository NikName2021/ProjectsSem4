#include "../include/Quantity.h"
#include <iostream>
#include <stdexcept>

Quantity::Quantity(double valSI, Dimension d) : valueSI(valSI), dim(d) {}

Quantity Quantity::fromUnit(double value, const Unit& unit) {
    return Quantity(value * unit.getFactor(), unit.getDimension());
}

Quantity Quantity::operator+(const Quantity& other) const {
    if (dim != other.dim) throw std::runtime_error("Physical Error: Different dimensions!");
    return Quantity(valueSI + other.valueSI, dim);
}

Quantity Quantity::operator*(const Quantity& other) const {
    return Quantity(valueSI * other.valueSI, dim + other.dim);
}

Quantity Quantity::operator/(const Quantity& other) const {
    if (other.valueSI == 0) throw std::runtime_error("Math Error: Division by zero!");
    return Quantity(valueSI / other.valueSI, dim - other.dim);
}

void Quantity::printSI() const {
    std::cout << valueSI << " (SI units: ";
    dim.print();
    std::cout << ")" << std::endl;
}

void Quantity::printAs(const Unit& unit) const {
    if (dim != unit.getDimension()) throw std::runtime_error("Output Error: Unit mismatch!");
    std::cout << (valueSI / unit.getFactor()) << " " << unit.getName() << std::endl;
}