#include <iostream>

#include "vector.h"

int main() {
  Vector v{5}; // Crée un Vector de taille 5
  // Assignation des valeurs
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] = i * 10; // Utilise operator[] pour assigner des valeurs
  }
  // Affichage des valeurs
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << "\n";
  // Utilisation du constructeur de copie
  Vector v_copy = v;
  // Affichage des valeurs de la copie
  for (size_t i = 0; i < 5; ++i) {
    std::cout << v_copy[i] << " ";
  }
  // Démonstration de l'opérateur d'affectation
  Vector v_assign{}; // Crée un Vector vide
  v_assign = v;      // Utilise l'opérateur d'affectation
  // Affichage des valeurs après affectation
  for (int i = 0; i < 5; ++i) {
    std::cout << v_assign[i] << " ";
  }
  std::cout << "\n";
}
