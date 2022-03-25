#include "textDisplay.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <istream>
#include <fstream>

TextDisplay::TextDisplay(std::shared_ptr<Information> info, int p_size): Display(info, p_size) {
    std::shared_ptr<std::istream> board(new std::ifstream("rectangular_layout.txt"));
    std::string s;
    while(std::getline(*board.get(), s)) {
        std::vector<char> row;
        for(char c : s) {
            row.emplace_back(c);
        }
        layout.emplace_back(row);
    }
    for(int i = 0; i < 19; ++i) {
        std::pair<int, int> xy = tile_info[i];
        std::string name = resources[info->board[2*i]];
        for(size_t c = 0; c < name.length(); ++c) {
            layout[xy.first][xy.second+c] = name[c];
        }
        int val = info->board[2*i+1];
        if (val < 10 && val != 7) {
            layout[xy.first + 1][xy.second + 2] = val+'0';
        } else if (val != 7) {
            layout[xy.first + 1][xy.second + 1] = val/10+'0';
            layout[xy.first + 1][xy.second + 2] = val%10+'0';
        }
    }
    if (g != -1) updateGeese(g);
}

TextDisplay::~TextDisplay() {}

std::string printInt(int n) {
    if (n < 10) return " " + std::to_string(n);
    else return std::to_string(n);
}

void TextDisplay::printBoard() {
    for(size_t i = 0; i < layout.size(); ++i) {
        for(size_t j = 0; j < layout[i].size(); ++j) {
            std::cout << layout[i][j];
        }
        std::cout << std::endl;
    }
}

void TextDisplay::printResidences(int builder) {
    std::cout << builders[builder] << " has built:" << std::endl;
    // basement
    if (b_info[builder].size() >= 3) {
        for(auto b : b_info[builder][2]) {
            std::cout << b << " B" << std::endl;
        }
    }
    // house
    if (b_info[builder].size() >= 4) {
        for(auto h : b_info[builder][3]) {
            std::cout << h << " H" << std::endl;
        }
    }
    // tower
    if (b_info[builder].size() >= 5) {
        for(auto t : b_info[builder][4]) {
            std::cout << t << " T" << std::endl;
        }
    }
}

void TextDisplay::printBuilders() {
    std::string name;
    for (int i = 0; i < p_size; ++i) {
        name = builders[i];
        name.resize(7, ' ');
        std::cout << "Builder " << name << " has " << b_info[i][1].front() << " building points, " << b_info[i][0][0] << " BRICK, " << b_info[i][0][1] << " ENERGY, " << b_info[i][0][2] << " GLASS, " << b_info[i][0][3] << " HEAT, " << b_info[i][0][4] << " WIFI." << std::endl;
    }
}

void TextDisplay::updateResidence(int v, int builder, std::string type, bool x) {
    if (!x) {
        std::vector<int> lose = payResources[type.front()];
        for(int i = 0; i < 5; ++i) {
            b_info[builder][0][i] -= lose[i];
        }
        if (type == "basement") {
            std::cout << "Builder " << builders[builder] << " has successfully built a basement at " << v << "." << std::endl;
        } else if (type == "house") {
            std::cout << "Builder " << builders[builder] << " has successfully built a house at " << v << "." << std::endl;
        } else {
            std::cout << "Builder " << builders[builder] << " has successfully built a tower at " << v << "." << std::endl;
        }
    }
    if (type.compare("basement") == 0) {
        if (b_info[builder].size() < 3) {
            std::vector<int> b_v {v};
            b_info[builder].emplace_back(b_v);
        } else {
            b_info[builder][2].emplace_back(v);
        }
    } else if (type.compare("house") == 0) {
        b_info[builder][2].erase(std::find(b_info[builder][2].begin(), 
                                           b_info[builder][2].end(), 
                                           v));
        if (b_info[builder].size() < 4) {
            std::vector<int> b_v {v};
            b_info[builder].emplace_back(b_v);
        } else {
            b_info[builder][3].emplace_back(v);
        }
    } else {
        b_info[builder][3].erase(std::find(b_info[builder][3].begin(),
                                           b_info[builder][3].end(),
                                           v));
        if (b_info[builder].size() < 5) {
            std::vector<int> b_v {v};
            b_info[builder].emplace_back(b_v);
        } else {
            b_info[builder][4].emplace_back(v);
        }
    }
    ++b_info[builder][1][0];
    std::pair<int, int> xy = v_info[v];
    layout[xy.first][xy.second] = builders[builder].front();
    layout[xy.first][xy.second + 1] = std::toupper(type.front());
}

void TextDisplay::updateRoad(int e, int b, bool x) {
    if (!x) {
        --b_info[b][0][3];
        --b_info[b][0][4];
        std::cout << "Builder " << builders[b] << " has successfully built a road at " << e << "." << std::endl;
    }
    std::pair<int, int> xy = e_info[e];
    layout[xy.first][xy.second] = builders[b].front();
    layout[xy.first][xy.second+1] = 'R';
}

void TextDisplay::updateGeese(int tile) {
    if (tile != -1) {
        std::pair<int, int> xy = geese_info[g];
        layout[xy.first][xy.second] = ' ';
        layout[xy.first][xy.second + 1] = ' ';
        layout[xy.first][xy.second + 2] = ' ';
        layout[xy.first][xy.second + 3] = ' ';
        layout[xy.first][xy.second + 4] = ' ';
        g = tile;
        xy = geese_info[g];
        layout[xy.first][xy.second] = 'G';
        layout[xy.first][xy.second + 1] = 'E';
        layout[xy.first][xy.second + 2] = 'E';
        layout[xy.first][xy.second + 3] = 'S';
        layout[xy.first][xy.second + 4] = 'E';
    }
}

void TextDisplay::updateResource(int builder, int resource, int num) {
    b_info[builder][0][resource] += num;
    if (num > 0) {
        std::cout << "Builder " << builders[builder] << " gained:" << std::endl;
        std::cout << num << " " << resources[resource] << std::endl;
    }
}

void TextDisplay::sellHouse(int b, int v, std::string type) {
    if (type == "basement") {
        b_info[b][2].erase(std::find(b_info[b][2].begin(), 
                                     b_info[b][2].end(),
                                     v));
        --b_info[b][0][2];
        --b_info[b][0][4];
        --b_info[b][1][0];
    } else if (type == "house") {
        b_info[b][3].erase(std::find(b_info[b][3].begin(),
                                     b_info[b][3].end(),
                                     v));
        ++b_info[b][0][0];
        ++b_info[b][0][1];
        --b_info[b][0][2];
        b_info[b][0][3] -= 3;
        b_info[b][1][0] -= 2;
    } else {
        b_info[b][4].erase(std::find(b_info[b][4].begin(),
                                     b_info[b][4].end(),
                                     v));
        --b_info[b][0][0];
        b_info[b][1][0] -= 3;
    }
    std::pair<int, int> xy = v_info[v];
    if (v < 10) {
        layout[xy.first][xy.second] = ' ';
        layout[xy.first][xy.second+1] = v + '0';
    } else {
        layout[xy.first][xy.second] = v / 10 + '0';
        layout[xy.first][xy.second+1] = v % 10 + '0';
    }
    std::cout << "You have successfully mortgaged your " << type << " at " << v << "!" << std::endl;
}

void TextDisplay::CP_Basement(int vertex){
    std::cout << vertex << std::endl;
}

void TextDisplay::CP_Next(){
    std::cout << "next" << std::endl;
}

