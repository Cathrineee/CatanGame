#include "LoadedDice.h"
#include <iostream>

LoadedDice::LoadedDice(int num): num{num} {}
LoadedDice::~LoadedDice() {}

int LoadedDice::rollDice() { return num; }

