#include "Random.h"

#include <algorithm>
#include <random>
#include <ctime>

bool Random::started = false;

int Random::nextInt(int min, int max) {
    if (started == false) {
        srand(time(nullptr));
        started = true;
    }

    return min + (rand() % (max - min + 1));
}

int* Random::nextArray(vector<int> list, unsigned int limit) {
    std::mt19937 rng(std::time(nullptr));
    int* result = new int[limit];

    std::shuffle(list.begin(), list.end(), rng);

    for (unsigned int i = 0; i < limit; i++) {
        result[i] = list[i];
    }

    return result;
}

int* Random::nextArray(int* list, int size, unsigned int limit) {
    std::mt19937 rng(std::time(nullptr));
    int* result = new int[limit];

    std::shuffle(list, list + size, rng);

    for (unsigned int i = 0; i < limit; i++) {
        result[i] = list[i];
    }

    return result;
}

vector<int> Random::nextVector(vector<int> list, unsigned int limit) {
    std::mt19937 rng(std::time(nullptr));
    vector<int> result(limit);

    std::shuffle(list.begin(), list.end(), rng);

    for (unsigned int i = 0; i < limit; i++) {
        result[i] = list[i];
    }

    return result;
}

