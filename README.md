# Ant Simulator — Projet POO

Projet réalisé dans le cadre du cours de Programmation Orientée Objet (EPFL), en binôme avec Clara.

Le projet consiste à simuler une fourmilière : des fourmis (ouvrières, soldats) et des termites évoluent dans un environnement torique, cherchent de la nourriture, communiquent par phéromones et interagissent avec des ennemis. La simulation est développée progressivement au fil de plusieurs étapes, chacune ajoutant de nouvelles fonctionnalités et un niveau de conception supplémentaire.

## Structure du dépôt

Chaque dossier `partieX` correspond à une étape du projet, la version la plus aboutie étant `partie5b` :

- `partie1` — briques de base : vecteurs 2D (`Vec2d`), positions toriques, génération aléatoire, sérialisation JSON.
- `partie2` — modélisation de l'environnement et des colonies (fourmis, déambulation).
- `partie3` — comportements et interactions entre entités.
- `partie4` — extension du modèle (phéromones, ennemis).
- `partie5` / `partie5b` — version finale : simulation graphique complète avec SFML, statistiques, interface.

Chaque étape suit la même organisation :
- `src/` — code source C++ (entités, environnement, utilitaires, JSON, tests).
- `res/` — ressources graphiques et polices utilisées par la simulation.
- `extlib/` — bibliothèques externes (Catch, pour les tests unitaires).

## Technologies

- C++14
- CMake
- [SFML](https://www.sfml-dev.org/) 2.5 (rendu graphique)
- [Catch](https://github.com/catchorg/Catch2) (tests unitaires)

## Compilation

Chaque étape se compile indépendamment via CMake, par exemple pour la version finale :

```bash
cd partie5b/src
mkdir build && cd build
cmake ..
make
```

SFML doit être installé sur la machine pour compiler les parties incluant la partie graphique (à partir de `partie5`).
