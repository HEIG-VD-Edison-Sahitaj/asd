/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Header file using for the generation of different types of vectors
Note        |   -
Source      |   -
--------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_GENERATEVECTOR_H
#define ASD2022_L1_COMPLEXITE_GENERATEVECTOR_H

#include <vector>
#include <random>
#include <algorithm>
#include "OpCounter.h"

enum Type {INCREASING, DECREASING, RANDOM, ALMOST};

/* ---------------------------
Name        | generateVector
Parameter(s)| size_t size, unsigned seed, Type sortingType
Return      | std::vector<T>
Goal        | Generate a vector of size with the given sorting type
--------------------------- */
template <typename T>
std::vector<T> generateVector(size_t size, unsigned seed, Type sortingType){
    std::vector<T> result(size);
    iota(result.begin(), result.end(), 0);
    std::default_random_engine randomSeed(seed);

    switch (sortingType) {
        default:
        case Type::INCREASING:
            return result;
        case Type::DECREASING:
            std::reverse(result.begin(), result.end());
            return result;
        case Type::RANDOM:
            std::shuffle(result.begin(), result.end(), randomSeed);
            return result;
        case Type::ALMOST:
            std::vector<T> randomVector = generateVector<T>(size, seed,Type::RANDOM);
            transform(result.begin(), result.end(), randomVector.begin(), result.begin(),
                      [&randomSeed](T a, T b) { return ((randomSeed() % 100) < 40) ? b : a; });
            return result;
    }
}

#endif //ASD2022_L1_COMPLEXITE_GENERATEVECTOR_H
