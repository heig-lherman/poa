#include "Operators.hpp"

long AddOperation::apply(const long a, const long b) const {
    return a + b;
}

long SubtractOperation::apply(const long a, const long b) const {
    return a - b;
}

long MultiplyOperation::apply(const long a, const long b) const {
    return a * b;
}
