#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <random>

class Dice{
    public:
    // rollDice() is a pure virtual function for rolling the dice
    virtual int rollDice() = 0;
};

#endif
