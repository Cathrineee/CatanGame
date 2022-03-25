#include "BuilderData.h"
#include <algorithm>

BuilderData::BuilderData(std::string data): numBricks{0}, numEnergies{0}, numGlass{0}, numHeat{0}, numWifi{0} {
    if (data != "") {
    size_t r_pos = data.find('r');
    size_t h_pos = data.find('h');
    size_t start = 0;
    size_t space = data.find(' ');
    numBricks = std::stoi(data.substr(start, space-start));
    start = space + 1;
    space = data.find(' ', start);
    numEnergies = std::stoi(data.substr(start, space-start));
    start = space + 1;
    space = data.find(' ', start);
    numGlass = std::stoi(data.substr(start, space - start));
    start = space + 1;
    space = data.find(' ', start);
    numHeat = std::stoi(data.substr(start, space - start));
    start = space + 1;
    space = data.find(' ', start);
    numWifi = std::stoi(data.substr(start, space - start));
    start = r_pos + 2;
    while(start < h_pos) {
        space = data.find(' ', start);
        road.emplace_back(std::stoi(data.substr(start, space-start)));
        start = space + 1;
    }
    start = h_pos + 2;
    while(start < data.size()) {
        space = data.find(' ', start);
        if (data[space+1] == 'B') {
            basement.emplace_back(std::stoi(data.substr(start, space-start)));
        } else if (data[space+1] == 'T') {
            tower.emplace_back(std::stoi(data.substr(start, space-start)));
        } else {
            house.emplace_back(std::stoi(data.substr(start, space-start)));
        }
        start = space + 3;
    } }
}

