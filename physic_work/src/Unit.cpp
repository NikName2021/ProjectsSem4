#include "../include/Unit.h"

Unit::Unit() : name(""), factor(1.0), dim(Dimension()) {}
Unit::Unit(std::string n, double f, Dimension d) : name(n), factor(f), dim(d) {}