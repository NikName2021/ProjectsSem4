#include <iostream>
#include "include/Quantity.h"

int main() {
    try {
        Dimension L(0, 1, 0);
        Dimension M(1, 0, 0);
        Dimension T(0, 0, 1);
        Dimension V(0, 1, -1);
        Dimension A(0, 1, -2);

        Unit kg("kg", 1.0, M);
        Unit m("m", 1.0, L);
        Unit s("s", 1.0, T);
        Unit km("km", 1000.0, L);
        Unit Newton("N", 1.0, Dimension(1, 1, -2));


        Quantity d1 = Quantity::fromUnit(500, m);
        Quantity d2 = Quantity::fromUnit(2, km);
        Quantity dTotal = d1 + d2;
        std::cout << "Distance: ";
        dTotal.printAs(km);


        Quantity mass = Quantity::fromUnit(10, kg);
        Quantity accel = Quantity::fromUnit(9.8, Unit("m/s^2", 1.0, A));
        Quantity force = mass * accel;
        std::cout << "Force: ";
        force.printAs(Newton);
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}
