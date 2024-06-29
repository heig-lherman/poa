#include "Vector2D.hpp"

#include <cmath>

Vector2D::Vector2D(int x, int y) {
    _x = x;
    _y = y;
}

int Vector2D::x() const {
    return _x;
}

int Vector2D::y() const {
    return _y;
}

void Vector2D::add(const Vector2D& other) {
    _x += other._x;
    _y += other._y;
}

// Distance to a diagonal cell is the same as an orthogonal cell
unsigned Vector2D::distance(const Vector2D& other) const {
    int dx = std::abs(other._x - _x);
    int dy = std::abs(other._y - _y);
    return static_cast<unsigned>(std::max(dx, dy));
}

Vector2D Vector2D::direction(const Vector2D& other) const {
    int dx = other._x - _x;
    int dy = other._y - _y;
    return Vector2D{dx == 0 ? 0 : dx / std::abs(dx), dy == 0 ? 0 : dy / std::abs(dy)};
}

bool Vector2D::equals(const Vector2D& other) const {
    return (_x == other._x) && (_y == other._y);
}
