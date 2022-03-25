#ifndef FAIRDICE_H
#define FAIRDICE_H

#include "dice.h"
#include <iostream>
#include <random>

class FairDice: public Dice {
    std::default_random_engine rng;
    std::vector<int> num;

    public:
    // constructor
    FairDice(int seed, std::vector<int> numbers);
    // destructor
    virtual ~FairDice();
    // rollDice() returns the rolling number
    int rollDice() override;
};

#endif
