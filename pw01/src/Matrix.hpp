#pragma once

#include "Operators.hpp"

/**
 * @brief Matrix implementation with operations applied in
 *        congruence with a modulus
 */
class Matrix {
    unsigned int** matrix;
    size_t rows{0};
    size_t cols{0};
    unsigned mod;

public:
    /**
     * @brief Construct a new random Matrix object of size rows x cols
     *        and with mod as the modulus
     *
     * @param rows number of rows
     * @param cols number of columns
     * @param mod modulus
     */
    Matrix(size_t rows, size_t cols, unsigned mod);

    /**
     * @brief Construct a new Matrix object from another matrix
     * @param other the matrix to copy
     */
    Matrix(const Matrix& other);

    /**
     * @brief Move constructor
     * @param other the matrix to own
     */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief Copy assignment operator
     * @param other the matrix to copy
     * @return Matrix& the updated matrix
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Move assignment operator
     * @param other the matrix to own
     * @return Matrix& the updated matrix
     */
    Matrix& operator=(Matrix&& other) noexcept;

    /**
     * @brief Destroy the Matrix object
     */
    ~Matrix();

    /**
     * @brief Get the values at position i, j
     * @param i
     * @param j
     * @return matrix[i][j] if i < rows and j < cols, 0 otherwise
     */
    [[nodiscard]] unsigned get(size_t i, size_t j) const;

    /**
     * @brief Add a matrix to the current matrix
     *
     * @param other the matrix to add
     * @return this matrix for chaining
     */
    Matrix& add(const Matrix& other);

    /**
     * @brief Subtract a matrix from the current matrix
     *
     * @param other the matrix to subtract
     * @return this matrix for chaining
     */
    Matrix& subtract(const Matrix& other);

    /**
     * @brief Multiply a matrix with the current matrix
     *
     * @param other the matrix to multiply
     * @return this matrix for chaining
     */
    Matrix& multiply(const Matrix& other);

    /**
     * @brief Calculate the addition of a matrix to the current matrix
     *
     * @param other the matrix to add
     * @return the resulting matrix
     */
    [[nodiscard]] Matrix addStatic(const Matrix& other) const;

    /**
     * @brief Calculate the subtraction of a matrix from the current matrix
     *
     * @param other the matrix to subtract
     * @return the resulting matrix
     */
    [[nodiscard]] Matrix subtractStatic(const Matrix& other) const;

    /**
     * @brief Calculate the product of a matrix with the current matrix
     *
     * @param other the matrix to multiply
     * @return the resulting matrix
     */
    [[nodiscard]] Matrix multiplyStatic(const Matrix& other) const;

    /**
     * @brief Calculate the addition of a matrix to the current matrix
     *
     * @param other the matrix to add
     * @return a pointer to the resulting matrix
     */
    [[nodiscard]] Matrix* addDynamic(const Matrix& other) const;

    /**
     * @brief Calculate the subtraction of a matrix from the current matrix
     *
     * @param other the matrix to subtract
     * @return a pointer to the resulting matrix
     */
    [[nodiscard]] Matrix* subtractDynamic(const Matrix& other) const;

    /**
     * @brief Calculate the product of a matrix with the current matrix
     *
     * @param other the matrix to multiply
     * @return a pointer to the resulting matrix
     */
    [[nodiscard]] Matrix* multiplyDynamic(const Matrix& other) const;

    /**
     * @brief Overloaded output operator
     *
     * @param os
     * @param matrix
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

private:
    /**
     * @brief Construct a new Matrix object without initializing the matrix
     * @param mod modulus
     */
    explicit Matrix(unsigned mod);

    /**
      * @brief Allocates memory for the matrix with a set size
      * @param newRows the number of rows
      * @param newColumns the number of columns
      */
    void initializeMatrix(size_t newRows, size_t newColumns);

    /**
     * @brief Fills the matrix with random values
     * @param reference a matrix to copy the values from, if null then the
     *                  matrix is filled with random values
     */
    void fillMatrix(const Matrix* reference = nullptr);

    /**
     * @brief Helper that deletes the matrix
     */
    void deleteMatrix();

    /**
     * @brief applies an operation to the matrix with the values of b
     * @param op the operation to apply
     * @param b the matrix to apply the operation with
     * @param container the matrix to store the result
     */
    void applyOperation(const Operation& op,
                        const Matrix& b,
                        Matrix& container) const;
};
