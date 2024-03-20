#include <iostream>
#include "Matrix.hpp"

int main(int argc, char** argv) {
    using std::cout;

    if (argc < 6) {
        std::cerr
            << "Usage: " << argv[0] << " rows1 cols1 rows2 cols2 mod"
            << std::endl;

        return 1;
    }

    unsigned rows1, cols1, rows2, cols2, mod;
    try {
        for (int i = 1; i < argc; i++) {
            if (std::stoi(argv[i]) < 0) {
                std::cerr
                    << "Invalid input: " << argv[i]
                    << " must be >= 0" << std::endl;

                return 1;
            }
        }

        rows1 = std::stoi(argv[1]);
        cols1 = std::stoi(argv[2]);
        rows2 = std::stoi(argv[3]);
        cols2 = std::stoi(argv[4]);
        mod = std::stoi(argv[5]);

        if (mod < 1) {
            std::cerr
                << "Invalid input: " << mod
                << " must be >= 1" << std::endl;

            return 1;
        }
    } catch (std::exception& e) {
        std::cerr << "Invalid input: " << e.what() << std::endl;
        return 1;
    }

    Matrix m1{rows1, cols1, mod};
    const Matrix m2{rows2, cols2, mod};

    cout << "The modulus is " << mod << "\n";
    cout << "one\n" << m1 << "\n";
    cout << "two\n" << m2 << "\n";

    cout << "Opérations avec retour par valeur" << "\n";
    cout << "one + two\n" << m1.addStatic(m2) << "\n";
    cout << "one - two\n" << m1.subtractStatic(m2) << "\n";
    cout << "one * two\n" << m1.multiplyStatic(m2) << "\n";

    cout << "Opérations avec retour par pointeur" << "\n";
    const Matrix* const addResult = m1.addDynamic(m2);
    const Matrix* const subtractResult = m1.subtractDynamic(m2);
    const Matrix* const multiplyResult = m1.multiplyDynamic(m2);
    cout << "one + two\n" << *addResult << "\n";
    cout << "one - two\n" << *subtractResult << "\n";
    cout << "one * two\n" << *multiplyResult << "\n";
    delete addResult;
    delete subtractResult;
    delete multiplyResult;

    cout << "Opérations avec modification de l'objet" << "\n";
    cout << "one += two\n" << m1.add(m2) << "\n";
    cout << "one -= two\n" << m1.subtract(m2) << "\n";
    cout << "one *= two\n" << m1.multiply(m2) << "\n";

    Matrix m3{2, 2, mod};
    cout << "three\n" << m3 << "\n";

    cout << "four copy constructed from three\n";
    Matrix m4{m3};
    cout << "four\n" << m4 << "\n";

    cout << "four copy assigned from three\n";
    m4 = m3.add(m4);
    cout << "three\n" << m3 << "\n";
    cout << "four\n" << m4 << "\n";

    return 0;
}
