#pragma once

/**
 * Class representing a 2D vector.
 */
class Vector2D {
public:
    /**
     * Constructor for a 2D vector.
     * @param x X position
     * @param y Y position
     */
    Vector2D(int x, int y);

    /**
     * Get X position
     * @return X position
     */
    [[nodiscard]] int x() const;

    /**
     * Get Y position
     * @return Y position
     */
    [[nodiscard]] int y() const;

    /**
     * Add another vector to this vector
     * @param other the other vector to add
     */
    void add(const Vector2D& other);

    /**
     * Get the distance between two vectors, considering orthogonal and diagonal moves
     * @param other the other vector
     * @return the distance between the two vectors
     */
    unsigned distance(const Vector2D& other) const;

    /**
     * Get the unit vector pointing from this vector to another
     * @param other the other vector
     * @return the unit vector pointing from this vector to the other
     */
    Vector2D direction(const Vector2D& other) const;

    /**
     * Check if two vectors are equal
     * @param other the other vector
     * @return true if the vectors are equal, false otherwise
     */
    bool equals(const Vector2D& other) const;

private:
    int _x;
    int _y;
};
