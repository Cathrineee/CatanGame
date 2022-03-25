#ifndef BUILDERDATA_H
#define BUILDERDATA_H

#include <vector>
#include <string>

class BuilderData{
    public:
    int numBricks;
    int numEnergies;
    int numGlass;
    int numHeat;
    int numWifi;
    std::vector<int> road;
    std::vector<int> basement;
    std::vector<int> house;
    std::vector<int> tower;

    BuilderData(std::string data = "");
};




#endif
