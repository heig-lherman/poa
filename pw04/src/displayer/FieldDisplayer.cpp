#include "FieldDisplayer.hpp"

#include <iostream>

#include "../Field.hpp"

static constexpr std::string CORNER = "+", VERTICAL_WALL = "¦", HORIZONTAL_WALL = "-",
                             EMPTY_CELL = " ";

using std::cout;
using std::endl;

static void displayHorizontalWall(size_t width) {
    cout << CORNER;
    for (size_t i = 0; i < width; i++) {
        cout << HORIZONTAL_WALL;
    }
    cout << CORNER << endl;
}

void FieldDisplayer::display(Field& field) {
    displayHorizontalWall(field.width());
    std::shared_ptr<Humanoid> h;

    int maxX = static_cast<int>(field.width());
    int maxY = static_cast<int>(field.height());
    for (int i = 0; i < maxX; i++) {
        cout << VERTICAL_WALL;
        for (int j = 0; j < maxY; j++) {
            h = field.at(Vector2D(i, j));
            if (h) {
                cout << h->symbol();
            } else {
                cout << EMPTY_CELL;
            }
        }
        cout << VERTICAL_WALL << "\n";
    }

    displayHorizontalWall(field.width());
}
