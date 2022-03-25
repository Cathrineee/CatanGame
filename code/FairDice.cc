#include "FairDice.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

FairDice::FairDice(int seed, std::vector<int> numbers): num{numbers} {
    rng.seed(seed);
}
FairDice::~FairDice() {}

int FairDice::rollDice() {
    std::shuffle(num.begin(), num.end(), rng);
    int ret = num[0];
    std::shuffle(num.begin(), num.end(), rng);
    return ret + num[0];
}
