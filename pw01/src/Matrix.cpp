#include <algorithm>
#include <iostream>
#include <random>
#include "Matrix.hpp"
#include "Utils.hpp"

// random generator for all matrices
#ifdef TESTING
// use a fixed seed for reproducibility in unit tests
static std::mt19937 gen(0);
#else
static std::random_device rd;
static std::mt19937 gen(rd());
#endif

static AddOperation addOperation;
static SubtractOperation subtractOperation;
static MultiplyOperation multiplyOperation;

Matrix::Matrix(const unsigned mod) : matrix{nullptr}, mod(mod) {
    if (mod == 0) {
        throw std::invalid_argument("Modulus cannot be 0");
    }
}

Matrix::Matrix(const size_t rows,
               const size_t cols,
               const unsigned mod) : Matrix(mod) {
    initializeMatrix(rows, cols);
    fillMatrix();
}

Matrix::~Matrix() {
    deleteMatrix();
}

Matrix::Matrix(const Matrix& other) : Matrix(other.mod) {
    initializeMatrix(other.rows, other.cols);
    fillMatrix(&other);
}

Matrix::Matrix(Matrix&& other) noexcept:
    matrix{other.matrix}, rows{other.rows},
    cols{other.cols}, mod{other.mod} {
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    other.mod = 1;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    deleteMatrix();

    mod = other.mod;
    initializeMatrix(other.rows, other.cols);
    fillMatrix(&other);

    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    deleteMatrix();
    rows = other.rows;
    cols = other.cols;
    mod = other.mod;
    matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    other.mod = 1;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    if (matrix.rows == 0 || matrix.cols == 0) {
        os << "[]" << std::endl;
        return os;
    }

    for (size_t i = 0; i < matrix.rows; i++) {
        for (size_t j = 0; j < matrix.cols; j++) {
            os << matrix.matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

void Matrix::initializeMatrix(const size_t newRows, const size_t newColumns) {
    rows = 0;
    cols = newColumns;
    matrix = new unsigned*[newRows];
    while (rows < newRows) {
        matrix[rows] = new unsigned[newColumns];
        ++rows;
    }
}

void Matrix::deleteMatrix() {
    if (matrix == nullptr) {
        return;
    }

    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
    matrix = nullptr;
}

void Matrix::fillMatrix(const Matrix* const reference) {
    std::uniform_int_distribution distrib{0u, mod - 1};
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = reference == nullptr
                               ? distrib(gen)
                               : reference->get(i, j);
        }
    }
}

unsigned Matrix::get(const size_t i, const size_t j) const {
    return i < rows && j < cols ? matrix[i][j] : 0;
}

void Matrix::applyOperation(const Operation& op,
                            const Matrix& b,
                            Matrix& container) const {
    if (mod != b.mod || mod != container.mod) {
        throw std::invalid_argument("modulus mismatch");
    }

    const size_t newRows = std::max(rows, b.rows);
    const size_t newCols = std::max(cols, b.cols);

    container.initializeMatrix(newRows, newCols);
    for (size_t i = 0; i < newRows; i++) {
        for (size_t j = 0; j < newCols; j++) {
            container.matrix[i][j] = floorMod(
                op.apply(get(i, j), b.get(i, j)),
                container.mod);
        }
    }
}

Matrix& Matrix::add(const Matrix& other) {
    *this = addStatic(other);
    return *this;
}

Matrix& Matrix::subtract(const Matrix& other) {
    *this = subtractStatic(other);
    return *this;
}

Matrix& Matrix::multiply(const Matrix& other) {
    *this = multiplyStatic(other);
    return *this;
}

Matrix Matrix::addStatic(const Matrix& other) const {
    Matrix result{mod};
    applyOperation(addOperation, other, result);
    return result;
}

Matrix Matrix::subtractStatic(const Matrix& other) const {
    Matrix result{mod};
    applyOperation(subtractOperation, other, result);
    return result;
}

Matrix Matrix::multiplyStatic(const Matrix& other) const {
    Matrix result{mod};
    applyOperation(multiplyOperation, other, result);
    return result;
}

Matrix* Matrix::addDynamic(const Matrix& other) const {
    return new Matrix{addStatic(other)};
}

Matrix* Matrix::subtractDynamic(const Matrix& other) const {
    return new Matrix{subtractStatic(other)};
}

Matrix* Matrix::multiplyDynamic(const Matrix& other) const {
    return new Matrix{multiplyStatic(other)};
}
