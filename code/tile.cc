#include "tile.h"
#include <map>
#include <vector>
#include <iostream>

std::map<int, std::vector<int>> tv = TileToVertex();

Tile::Tile(int Num, int value, int Resource): Num{Num}, value{value}, 
Resource{Resource}, Vertexes{tv[Num]}{}

int Tile::getResource(){
    return Resource;
}

int Tile::getValue(){
    return value;
}

int Tile::getNum(){
    return Num;
}

