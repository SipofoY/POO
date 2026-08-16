# Ant Simulator — OOP Project

Project completed as part of the Object-Oriented Programming course at EPFL, in a team of two with Clara.

The project simulates an anthill: ants (workers, soldiers) and termites move around a toroidal environment, search for food, communicate via pheromones, and interact with enemies. The simulation was built incrementally across several stages, each adding new features and a further level of design.

## Repository structure

Each `partieX` folder corresponds to a stage of the project, with `partie5b` being the most complete version:

- `partie1` — basic building blocks: 2D vectors (`Vec2d`), toric positions, random generation, JSON serialization.
- `partie2` — modeling of the environment and colonies (ants, wandering behavior).
- `partie3` — behaviors and interactions between entities.
- `partie4` — model extension (pheromones, enemies).
- `partie5` / `partie5b` — final version: full graphical simulation with SFML, statistics, interface.

Each stage follows the same layout:
- `src/` — C++ source code (entities, environment, utilities, JSON, tests).
- `res/` — graphical resources and fonts used by the simulation.
- `extlib/` — external libraries (Catch, for unit testing).

## Technologies

- C++14
- CMake
- [SFML](https://www.sfml-dev.org/) 2.5 (graphics rendering)
- [Catch](https://github.com/catchorg/Catch2) (unit testing)

## Building

Each stage is built independently via CMake, for example for the final version:

```bash
cd partie5b/src
mkdir build && cd build
cmake ..
make
```

SFML must be installed to build the stages that include the graphical part (from `partie5` onward).
