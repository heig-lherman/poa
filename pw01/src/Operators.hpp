#pragma once

/**
 * @brief Defines an abstract operation that can be applied against two integers.
 */
class Operation {
public:
    virtual ~Operation() = default;

    /**
     * @brief Applies the operation to the two operands
     *
     * @param a The first operand
     * @param b The second operand
     * @return The result of the operation
     */
    [[nodiscard]] inline virtual long apply(long a, long b) const = 0;
};

/**
 * @brief Implementation of the addition operation
 */
class AddOperation final : public Operation {
public:
    [[nodiscard]] long apply(long a, long b) const override;
};

/**
 * @brief Implementation of the subtraction operation
 */
class SubtractOperation final : public Operation {
public:
    [[nodiscard]] long apply(long a, long b) const override;
};

/**
 * @brief Implementation of the multiplication operation
 */
class MultiplyOperation final : public Operation {
public:
    [[nodiscard]] long apply(long a, long b) const override;
};
