#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension {
private:
    int m, l, t;
public:
    Dimension(int mass = 0, int length = 0, int time = 0);

    bool operator==(const Dimension& other) const;
    bool operator!=(const Dimension& other) const;

    Dimension operator+(const Dimension& other) const;
    Dimension operator-(const Dimension& other) const;

    void print() const;
};

#endif