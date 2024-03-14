/*********
 *
 * But de l'exercice:
 *  - compiler et exécuter le programme.
 *  - prendre note de la sortie du programme - observer le comportement de la
 *sémantique de copie.
 *  - implémenter le constructeur de déplacemenent et l'affectation de
 *déplacement afine de compléter la règle des cinq.
 *  - prendre note de la sortie du programme - observer le comportement de la
 *sémantique de déplacement.
 *
 * Note: modifier uniquement la classe Vector, le programme de test en dessous
 *devra rester identique.
 *
 *************/

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

/**
 * @brief Classe représentant un vecteur de n-éléments avec un nom.
 *
 * Démontre la règle des trois et inclut un nom pour le vecteur.
 */
class Vector {
public:
  /**
   * @brief Construit un vecteur d'une taille donnée avec un nom.
   *
   * @param sz Taille du vecteur à créer.
   * @param name Nom du vecteur.
   */
  Vector(size_t sz, const std::string &name)
      : data_{new int[sz]{}}, sz_{sz}, name_{name} {
    std::cout << name_ << " : constructed" << std::endl;
  }

  /**
   * @brief Destructeur qui libère la mémoire allouée au vecteur.
   */
  ~Vector() {
    std::cout << name_ << " : destructed" << std::endl;
    delete[] data_;
  }

  /**
   * @brief Constructeur de copie qui crée une copie d'un vecteur existant, y
   * compris son nom.
   *
   * @param other Le vecteur à copier.
   */
  Vector(const Vector &other)
      : data_{new int[other.sz_]}, sz_{other.sz_}, name_{other.name_} {
    std::cout << name_ << " : copy constructed from: " << other.name_
              << std::endl;
    std::copy(other.data_, other.data_ + other.sz_, data_);
  }

  /**
   * @brief Constructeur de déplacement qui déplace le contenu d'un vecteur
   * existant dans un autre, y compris son nom.
   *
   * @param other Le vecteur à déplacer.
   */
  Vector(Vector &&other)
      : data_{other.data_}, sz_{other.sz_}, name_{other.name_} {
    std::cout << name_ << " : move constructed from: " << other.name_
              << std::endl;
    other.data_ = nullptr;
    other.sz_ = 0;
    other.name_ = "";
  }

  /**
   * @brief Opérateur d'affectation qui copie le contenu d'un vecteur dans un
   * autre, y compris son nom. Utilise l'idiome "copy and swap" (other est
   * passé par copie).
   *
   * @param other Le vecteur à copier.
   * @return Vector& Référence au vecteur actuel après copie.
   */
  Vector &operator=(Vector other) {
    std::cout << name_ << " : assigned from " << other.name_ << std::endl;
    std::swap(data_, other.data_);
    std::swap(sz_, other.sz_);
    std::swap(name_, other.name_);
    return *this;
  }

  /**
   * @brief Opérateur d'affectation qui déplace le contenu d'un vecteur dans un
   * autre.
   *
   * @param other Le vecteur à déplacer.
   */
  Vector &operator=(Vector &&other) {
    std::cout << name_ << " : move assigned from " << other.name_ << std::endl;
    delete[] data_;
    data_ = other.data_;
    sz_ = other.sz_;
    name_ = other.name_;
    return *this;
  }

  /**
   * @brief Accède à un élément du vecteur par son indice.
   *
   * @param index L'indice de l'élément à accéder.
   * @return int& Référence à l'élément à l'indice spécifié.
   */
  int &operator[](size_t index) { return data_[index]; }

  /**
   * @brief Accède à un élément du vecteur par son indice (version const).
   *
   * @param index L'indice de l'élément à accéder.
   * @return const int& Référence const à l'élément à l'indice spécifié.
   */
  const int &operator[](size_t index) const { return data_[index]; }

  /**
   * @brief Retourne la taille du vecteur.
   *
   * @return size_t La taille du vecteur.
   */
  size_t size() const { return sz_; }

  /**
   * @brief Retourne le nom du vecteur.
   *
   * @return const std::string& Le nom du vecteur.
   */
  const std::string &name() const { return name_; }

private:
  int *data_; ///< Pointeur vers le tableau contenant les éléments du vecteur.
  size_t sz_; ///< Taille du vecteur.
  std::string name_; ///< Nom du vecteur.
};

// ***************** Ne pas éditer le code de test ci dessous ******************
// //
#include <type_traits>

const void printVectorInfo(const Vector &v) {
  std::cout << "Vector information:" << std::endl;
  std::cout << "    Name: " << v.name() << std::endl;
  std::cout << "    Size: " << v.size() << std::endl;
  std::cout << "    Memory address of first element: " << std::hex << &v[0]
            << std::endl;
  std::cout << "    Memory address of vector: " << std::hex << &v << std::endl;
}

Vector createVector() {
  Vector v(5, "VectorFromFun");
  std::cout << "VectorFromFun, crée dans la fonction createVector:"
            << std::endl;
  printVectorInfo(v);
  return v;
}

void processVector(Vector v) {
  std::cout << "VectorFromFun dans processVector:" << std::endl;
  printVectorInfo(v);
}

int main() {
  Vector v1(5, "Vector1");
  std::cout << "v1 avant déplacement :\n";
  printVectorInfo(v1);

  // Tentative de "déplacer" v1 dans v2 (mais fait une copie à la place)
  Vector v2 = std::move(v1);

  std::cout << "v1 - après tentative de déplacement de v1 dans v2:"
            << std::endl;
  printVectorInfo(v1);
  std::cout << "v2 - après tentative de déplacement de v1 dans v2:"
            << std::endl;
  printVectorInfo(v2);

  // Tentative de déplacer v2 dans un autre vecteur lors du retour d'une
  // fonction
  Vector vectorFromFun = createVector();
  std::cout << "VectorFromFun, tel que retourné par createVector()"
            << std::endl;
  printVectorInfo(vectorFromFun);

  // Passage d'un temporaire à process vector
  std::cout << "Passage de VectorFromFun avec tentative de déplacement à "
               "processVector"
            << std::endl;
  processVector(std::move(vectorFromFun));

  std::cout << "processVector(createVector())" << std::endl;
  processVector(createVector());

  return 0;
}
