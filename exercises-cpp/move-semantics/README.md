# Exercices sur la Sémantique de Copie et de Déplacement en C++

Ces exercices sont conçus pour vous aider à comprendre et à pratiquer la sémantique de copie et de déplacement en C++, ainsi qu'à implémenter la règle des cinq dans une classe personnalisée. Vous travaillerez avec une classe `Vector` représentant un vecteur de n-éléments avec un nom.

## Objectifs

1. Compiler et exécuter le programme fourni pour observer la sémantique de copie en action.
2. Modifier la classe `Vector` pour implémenter le constructeur de déplacement et l'affectation de déplacement afin de compléter la règle des cinq.
3. Compiler et exécuter à nouveau le programme pour observer le comportement de la sémantique de déplacement.

## Exercice 1: Observation de la Sémantique de Copie

**But**: Compiler et exécuter le programme fourni pour observer le comportement de la sémantique de copie.

**Instructions**:
- Compilez le programme C++ fourni sans apporter de modifications. **Important:** si vous utilisez clang++ ou g++, veillez à utiliser l'option de compilation '--fno-elide-constructors', afin de désactiver les optimisations d'élimination de la copie faite par certains compiplateurs.

Exemple de commande de compilation avec GCC :
```bash
  g++ -std=c++17 -fno-elide-constructors -o vector-copy vectormove.cpp
```

- Exécutez le programme et prenez note de la sortie, en particulier déterminer ou et quand se passent les opérations de construction, de copie et de destruction des objets `Vector`.

## Exercice 2: la Sémantique de Déplacement

**But**: Compléter la règle des cinq en implémentant le constructeur de déplacement et l'affectation de déplacement dans la classe `Vector`.

**Instructions**:
- Ajoutez un constructeur de déplacement à la classe `Vector` qui s'approprie les ressources de l'objet source et laisse l'objet source dans un état valide mais indéfini.
- Implémentez l'opérateur d'affectation de déplacement en suivant une approche similaire.
- Assurez-vous que les opérations de déplacement affichent des messages appropriés sur la console pour faciliter l'observation de leur comportement lors de l'exécution.
- Compilez le programme après avoir ajouté la sémantique de déplacement à la classe `Vector`. **Important:** si vous utilisez clang++ ou g++, veillez à utiliser l'option de compilation `--fno-elide-constructors`, afin de désactiver les optimisations d'élimination de la copie faite par certains compiplateurs.
- Exécutez le programme et observez la différence dans la sortie, en particulier la manière dont les objets `Vector` sont déplacés au lieu d'être copiés.

Exemple de commande de compilation avec GCC :
```bash
  g++ -std=c++17 -fno-elide-constructors -o vector-move vectormove.cpp
```

## Bonus : Comprendre la l'évitement de copie (Copy Elision)

L'évitement de copie (**Copy Elision**) est une optimisation effectuée par les compilateurs pour réduire ou éliminer les opérations de copie inutiles d'objets. En C++, cela peut se produire dans plusieurs contextes, notamment lors du retour d'un objet par valeur d'une fonction ou lors de l'initialisation d'un objet avec une expression temporaire. Les compilateurs GCC et Clang appliquent agressivement cette optimisation conformément au standard C++.

### Contextes de la Copy Elision

La Copy Elision peut se produire dans les contextes suivants :

1. **Initialisation directe ou par copie** : Lorsqu'un objet est initialisé directement à partir d'un autre objet ou d'une expression temporaire, le compilateur peut éluder la copie.
   
2. **Retour d'une fonction** : Lorsqu'une fonction retourne un objet par valeur, le compilateur peut éviter de créer et de copier l'objet temporaire.

3. **Passage d'un objet par valeur à une fonction** : Lorsqu'un objet est passé à une fonction par valeur, le compilateur peut éviter de copier l'objet dans le paramètre de la fonction.

### Observer la Copy Elision en Action

**But** :Compiler avec GCC ou Clang pour observer la Copy Elision en action.

**Instructions** :

- Compilez le programme avec GCC ou Clang **sans utiliser** l'option `-fno-elide-constructors` afin de réactiver la Copy Elision. Comparez la sortie avec et sans cette option pour observer l'effet de la Copy Elision.
  
Exemple de commande de compilation avec GCC :
```bash
g++ -std=c++17 -o vector-elide vectormove.cpp
```

## Remarques

- Veillez à ne modifier que la classe `Vector`. Le programme de test (`main`) doit rester inchangé pour garantir que les modifications apportées à la classe `Vector` sont correctement validées.
- Réfléchissez à l'impact de la sémantique de déplacement sur les performances du programme, en particulier en ce qui concerne les opérations de copie coûteuses des ressources allouées dynamiquement.
