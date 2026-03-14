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
    std::cout << "M^" << m << " L^" << l << " T^" << t;
}