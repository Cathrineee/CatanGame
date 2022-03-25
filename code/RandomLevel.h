#ifndef RANDOMLEVEL_H
#define RANDOMLEVEL_H

#include "InitialLevel.h"
#include <random>
#include <memory>
#include <iostream>

class RandomLevel : public Level {
    std::default_random_engine rng;
    void updateInfo() override;

    public:
    RandomLevel(int p_size, int seed);
    virtual ~RandomLevel();
};

#endif
