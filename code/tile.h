#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <vector>
#include "helper.h"

class Tile {
    int Num;
    int value;
    int Resource;

    public:
    std::vector<int> Vertexes;
    // constructor
    Tile(int Num, int value, int Resource);

    // getResource() returns the resource of the tile
    int getResource();

    // getValue() returns the value of the tile
    int getValue();

    // getNum() returns the number of the tile
    int getNum();
};

#endif
