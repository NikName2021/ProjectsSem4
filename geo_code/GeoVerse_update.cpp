#include <iostream>
#include <cmath>
#include <optional>
#include <vector>
#include <iomanip>

#ifndef M_PI
#endif

struct Vector {
    double dx, dy;
    double length() const { return std::sqrt(dx * dx + dy * dy); }
    double atan2() const { return std::atan2(dy, dx) * 180.0 / M_PI; }
    Vector normalize() const {
        double len = length();
        return (len < 1e-9) ? Vector{ 0, 0 } : Vector{ dx / len, dy / len };
    }
    Vector operator*(double scalar) const { return { dx * scalar, dy * scalar }; }
    Vector operator/(double scalar) const { return { dx / scalar, dy / scalar }; }

    Vector operator~() const { return { -dy, dx }; }

    double operator^(const Vector& other) const {
        double angle = atan2() - other.atan2();
        while (angle > 180.0) angle -= 360.0;
        while (angle < -180.0) angle += 360.0;
        return std::abs(angle);
    }
};

inline Vector operator*(double scalar, const Vector& v) { return v * scalar; }

struct Line;

struct Point {
    double x, y;
    Vector operator-(const Point& other) const { return { x - other.x, y - other.y }; }
    Point operator+(const Vector& v) const { return { x + v.dx, y + v.dy }; }

    Line operator|(const Point& other) const;
    Line operator|(const Vector& dir) const;
};

struct Line {
    Point p1, p2;
    double a, b, c;

    Line(Point p1, Point p2) : p1(p1), p2(p2) {
        Vector norm = Vector{ p2.y - p1.y, p1.x - p2.x }.normalize();
        a = norm.dx; b = norm.dy;
        c = -a * p1.x - b * p1.y;
    }

    std::optional<Point> operator&(const Line& other) const {
        double det = a * other.b - other.a * b;
        if (std::abs(det) < 1e-9) return std::nullopt;
        return Point{(other.c * b - c * other.b) / det, (c * other.a - other.c * a) / det};
    }

    Vector operator~() const { return { a, b }; }
};

inline Line Point::operator|(const Point& other) const { return Line(*this, other); }
inline Line Point::operator|(const Vector& dir) const { return Line(*this, *this + dir); }

struct Circle {
    Point center;
    double radius;

    Circle(Point c, double r) : center(c), radius(r) {}

    Point pointAtAngle(double degrees) const {
        double rad = degrees * M_PI / 180.0;
        return { center.x + radius * std::cos(rad), center.y + radius * std::sin(rad) };
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Point O{ 0, 0 };
    double R = 100.0;
    Circle circle(O, R);

    Point A = circle.pointAtAngle(30);
    Point C = circle.pointAtAngle(150);

    double centralAngle = (A - O) ^ (C - O);

    std::cout << "--- Доказательство теоремы о вписанном угле ---\n";
    std::cout << "Центральный угол AOC: " << centralAngle << " град.\n\n";

    std::vector<double> testAngles = { 210, 270, 330 };

    for (double angleB : testAngles) {
        Point B = circle.pointAtAngle(angleB);
        double inscribedAngle = (A - B) ^ (C - B);

        std::cout << "Точка B на отметке " << (int)angleB << "°:\n";
        std::cout << "  Вписанный угол ABC: " << inscribedAngle << " град.\n";
        std::cout << "  Удвоенный вписанный (2 * ABC): " << (2 * inscribedAngle)
                  << " (Ожидалось: " << centralAngle << ")\n";

        if (std::abs(2 * inscribedAngle - centralAngle) < 1e-5) {
            std::cout << "  РЕЗУЛЬТАТ: Теорема подтверждена!\n\n";
        } else {
            std::cout << "  РЕЗУЛЬТАТ: Ошибка (возможно, точка на другой дуге).\n\n";
        }
    }

    Point D1 = circle.pointAtAngle(0);
    Point D2 = circle.pointAtAngle(180);
    Point B_any = circle.pointAtAngle(75);
    double rightAngle = (D1 - B_any) ^ (D2 - B_any);

    std::cout << "--- Частный случай: Угол на диаметре ---\n";
    std::cout << "Угол, опирающийся на диаметр: " << rightAngle
              << " град. (Ожидалось: 90.00)\n";

    return 0;
}