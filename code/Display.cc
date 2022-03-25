#include "Display.h"
#include <iostream>

Display::Display(std::shared_ptr<Information> info, int p_size): p_size{p_size} {
    builders[0] = "BLUE";
    builders[1] = "RED";
    if (p_size >= 3) {
        builders[2] = "ORANGE";
    }
    if (p_size == 4) {
        builders[3] = "YELLOW";
    }
    resources[0] = "BRICK";
    resources[1] = "ENERGY";
    resources[2] = "GLASS";
    resources[3] = "HEAT";
    resources[4] = "WIFI";
    resources[5] = "PARK";

    // record builder's resources
    std::vector<int> r { info->builder0Data.numBricks, 
                         info->builder0Data.numEnergies, 
                         info->builder0Data.numGlass, 
                         info->builder0Data.numHeat, 
                         info->builder0Data.numWifi };
    b_info[0].emplace_back(r);
    r = { info->builder1Data.numBricks,
          info->builder1Data.numEnergies,
          info->builder1Data.numGlass,
          info->builder1Data.numHeat,
          info->builder1Data.numWifi };
    b_info[1].emplace_back(r);
    if (p_size >= 3) {
        r = {info->builder2Data.numBricks,
             info->builder2Data.numEnergies,
             info->builder2Data.numGlass,
             info->builder2Data.numHeat,
             info->builder2Data.numWifi};
        b_info[2].emplace_back(r);
    }
    if (p_size == 4) {
        r = {info->builder3Data.numBricks,
             info->builder3Data.numEnergies,
             info->builder3Data.numGlass,
             info->builder3Data.numHeat,
             info->builder3Data.numWifi};
        b_info[3].emplace_back(r);
    }

    // initialize builder's building points
    r = { 0 };
    b_info[0].emplace_back(r);
    b_info[1].emplace_back(r);
    if (p_size >= 3) {
        b_info[2].emplace_back(r);
    }
    if (p_size == 4) {
        b_info[3].emplace_back(r);
    }

    // initialize tile coordinates
    std::pair<int, int> xy;
    for(int i = 0; i < 19; ++i) {
        if (i == 0) xy = std::make_pair(5, 25);
        else if (i == 1) xy = std::make_pair(9, 15);
        else if (i == 2) xy = std::make_pair(9, 35);
        else if (i == 3) xy = std::make_pair(13, 5);
        else if (i == 4) xy = std::make_pair(13, 25);
        else if (i == 5) xy = std::make_pair(13, 45);
        else if (i == 18) xy = std::make_pair(37, 25);
        else {
            xy.first = geese_info[i-5].first + 8;
            xy.second = geese_info[i-5].second;
        }
        geese_info.emplace(i, xy);
    }

    for(int i = 0; i < 19; ++i) {
        if (i == 0) xy = std::make_pair(3, 25);
        else if (i == 1) xy = std::make_pair(7, 15);
        else if (i == 2) xy = std::make_pair(7, 35);
        else if (i == 3) xy = std::make_pair(11, 5);
        else if (i == 4) xy = std::make_pair(11, 25);
        else if (i == 5) xy = std::make_pair(11, 45);
        else if (i == 18) xy = std::make_pair(35, 25);
        else {
            xy.first = tile_info[i-5].first + 8;
            xy.second = tile_info[i-5].second;
        }
        tile_info.emplace(i, xy);
    }

    g = info->geese;

    // initialize vertex coordinates
    for(int i = 0; i < 54; ++i) {
        if (i == 0) xy = std::make_pair(0, 21);
        else if (i == 1) xy = std::make_pair(0, 31);
        else if (i == 2) xy = std::make_pair(4, 11);
        else if (i == 3) xy = std::make_pair(4, 21);
        else if (i == 4) xy = std::make_pair(4, 31);
        else if (i == 5) xy = std::make_pair(4, 41);
        else if (i == 6) xy = std::make_pair(8, 1);
        else if (i == 7) xy = std::make_pair(8, 11);
        else if (i == 8) xy = std::make_pair(8, 21);
        else if (i == 9) xy = std::make_pair(8, 31);
        else if (i == 10) xy = std::make_pair(8, 41);
        else if (i == 11) xy = std::make_pair(8, 51);
        else if (i == 48) xy = std::make_pair(36, 11);
        else if (i == 49) xy = std::make_pair(36, 21);
        else if (i == 50) xy = std::make_pair(36, 31);
        else if (i == 51) xy = std::make_pair(36, 41);
        else if (i == 52) xy = std::make_pair(40, 21);
        else if (i == 53) xy = std::make_pair(40, 31);
        else {
            xy.first = v_info[i-6].first + 4;
            xy.second = v_info[i-6].second;
        }
        v_info.emplace(i, xy);
    }

    // initialize edge coordinates
    for(int i = 0; i < 72; ++i) {
        if (i == 0) xy = std::make_pair(0, 26);
        else if (i == 1) xy = std::make_pair(2, 21);
        else if (i == 2) xy = std::make_pair(2, 31);
        else if (i == 3) xy = std::make_pair(4, 16);
        else if (i == 4) xy = std::make_pair(4, 36);
        else if (i == 5) xy = std::make_pair(6, 11);
        else if (i == 6) xy = std::make_pair(6, 21);
        else if (i == 7) xy = std::make_pair(6, 31);
        else if (i == 8) xy = std::make_pair(6, 41);
        else if (i == 9) xy = std::make_pair(8, 6);
        else if (i == 10) xy = std::make_pair(8, 26);
        else if (i == 11) xy = std::make_pair(8, 46);
        else if (i == 12) xy = std::make_pair(10, 1);
        else if (i == 13) xy = std::make_pair(10, 11);
        else if (i == 14) xy = std::make_pair(10, 21);
        else if (i == 15) xy = std::make_pair(10, 31);
        else if (i == 16) xy = std::make_pair(10, 41);
        else if (i == 17) xy = std::make_pair(10, 51);
        else if (i == 18) xy = std::make_pair(12, 16);
        else if (i == 19) xy = std::make_pair(12, 36);
        else if (i == 63) xy = std::make_pair(34, 11);
        else if (i == 64) xy = std::make_pair(34, 21);
        else if (i == 65) xy = std::make_pair(34, 31);
        else if (i == 66) xy = std::make_pair(34, 41);
        else if (i == 67) xy = std::make_pair(36, 16);
        else if (i == 68) xy = std::make_pair(36, 36);
        else if (i == 69) xy = std::make_pair(38, 21);
        else if (i == 70) xy = std::make_pair(38, 31);
        else if (i == 71) xy = std::make_pair(40, 26);
        else if (i % 17 == 0 || 
                (i % 17 >= 12 && i % 17 <= 16)) {
            xy.first = e_info[i-9].first + 4;
            xy.second = e_info[i-9].second;
        } else if (i % 17 >= 3 && i % 17 <= 8) {
            xy.first = e_info[i-8].first + 4;
            xy.second = e_info[i-8].second;
        }
        else {
            xy.first = e_info[i-17].first + 8;
            xy.second = e_info[i-17].second;
        }
        e_info.emplace(i, xy);
    }

    payResources['b'] = {1,1,1,0,1};
    payResources['h'] = {0,0,2,3,0};
    payResources['t'] = {3,2,2,2,1};
    payResources['r'] = {0,0,0,1,1};

    building[4] = "Road";
    building[1] = "Basement";
    building[2] = "House";
    building[3] = "Tower";
}
Display::~Display() {}

void Display::wrongGeeseLocation() {
    std::cerr << "ERROR: invalid Geese location." << std::endl;
}

void Display::geeseHalfReport(int cur, int num, int energy, int brick, int glass, int heat, int wifi) {
    b_info[cur][0][0] -= brick;
    b_info[cur][0][1] -= energy;
    b_info[cur][0][2] -= glass;
    b_info[cur][0][3] -= heat;
    b_info[cur][0][4] -= wifi;
    std::cout << "Builder " << builders[cur] << " loses " << num << " resources to the geese. They lose:" << std::endl;
    if (brick != 0) std::cout << brick << " BRICK" << std::endl;
    if (energy != 0) std::cout << energy << " ENERGY" << std::endl;
    if (glass != 0) std::cout << glass << " GLASS" << std::endl;
    if (heat != 0) std::cout << heat << " HEAT" << std::endl;
    if (wifi != 0) std::cout << wifi << " WIFI" << std::endl;
}

void Display::availableBuilders(int cur, std::set<std::string> builder) {
    if (builder.empty()) std::cout << "Builder " << builders[cur] << " has no builders to steal from." << std::endl;
    else {
    std::cout << "Builder " << builders[cur] << " can choose to steal from";
    for (auto b = builder.begin(); b != builder.end(); ++b) {
        if (b != builder.begin()) std::cout << ",";
        std::cout << " " << *b;
    }
    std::cout << "." << std::endl;
    }
}

void Display::stealMessage(int currentB, int b, int resource) {
    ++b_info[currentB][0][resource];
    --b_info[b][0][resource];
    std::cout << "Builder " << builders[currentB] << " steals " << resources[resource] << " from builder " << builders[b] << "." << std::endl;
}

void Display::invalidFile() {
    std::cerr << "Something went wrong when loading." << std::endl << std::endl;
}

void Display::invalidBuild() {
    std::cerr << "You cannot build here." << std::endl;
}

void Display::rebuild(std::vector<int> v) {
    std::cerr << "You cannot build here." << std::endl << std::endl;
    std::cerr << "Basement already exists at the following positions: ";
    for(int i : v) {
        std::cerr << i << " ";
    }
    std::cerr << std::endl;
}

void Display::noEnoughRes(int type, int builder) {
    if (builder == -1 && type != -1) {
        if (type != 5) {
            char t = std::tolower(building[type].front());
            std::cerr << "You do not have enough resources." << std::endl;
            std::cerr << std::endl;
            std::cerr << "Building a " << building[type] << " requires ";
            for (int i = 0; i < 5; ++i) {
                if (payResources[t][i] != 0) {
                    std::cerr << payResources[t][i] << " " << resources[i] << " ";
                }
            }
            std::cerr << std::endl;
        } else {
            std::cerr << "You do not have enough resources to complete the exchange." << std::endl;
        }
    } else if (type == -1) {
        if (builder == -1) {
            std::cerr << "You do not have enough resources to complete this trade." << std::endl;
        } else {
            std::cerr << "Builder " << builders[builder] << " does not have enough resources to complete this trade." << std::endl;
        }
    }
}

void Display::improveTower() {
    std::cerr << "You cannot improve a tower." << std::endl;
}

void Display::NoResourceMessage() {
    std::cout << "No builders gained resources." << std::endl;
}

void Display::CannotSaleHouse(int v) {
    std::cerr << "You cannot apply for the mortgage at " << v << "." << std::endl;
}
