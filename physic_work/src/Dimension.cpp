#include "../include/Dimension.h"
#include <iostream>

Dimension::Dimension(int mass, int length, int time) : m(mass), l(length), t(time) {}

bool Dimension::operator==(const Dimension& other) const {
    return (m == other.m && l == other.l && t == other.t);
}

bool Dimension::operator!=(const Dimension& other) const {
    return !(*this == other);
}

Dimension Dimension::operator+(const Dimension& other) const {
    return Dimension(m + other.m, l + other.l, t + other.t);
}

Dimension Dimension::operator-(const Dimension& other) const {
    return Dimension(m - other.m, l - other.l, t - other.t);
}
void Dimension::print() const {
    bool first = true;

    auto printUnit = [&](int power, std::string symbol) {
        if (power == 0) return;

        if (!first) std::cout << "*";
        std::cout << symbol;
        if (power != 1) std::cout << "^" << power;

        first = false;
    };

    printUnit(m, "kg");
    printUnit(l, "m");
    printUnit(t, "s");

    if (first) std::cout << "1";
}