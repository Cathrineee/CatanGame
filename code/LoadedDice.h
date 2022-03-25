#ifndef LOADEDDICE_H
#define LOADEDDICE_H

#include "dice.h"

class LoadedDice: public Dice {
    int num;

    public:
    // constructor
    LoadedDice(int num);
    // destructor
    virtual ~LoadedDice();
    // rollDice() returns the number after rolling the dice
    int rollDice() override;
};

#endif
