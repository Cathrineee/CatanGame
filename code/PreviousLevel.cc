#include "PreviousLevel.h"
#include <string>

PreviousLevel::PreviousLevel(int p_size, std::shared_ptr<std::istream> f): Level(p_size), f{f} {}
PreviousLevel::~PreviousLevel() {}

void PreviousLevel::updateInfo() {
    int p = 2;
    std::string s;
    std::getline(*f.get(), s);
    info->CurTurn = std::stoi(s);
    std::getline(*f.get(), s);
    info->builder0Data = BuilderData(s);
    std::getline(*f.get(), s);
    info->builder1Data = BuilderData(s);
    std::getline(*f.get(), s);
    if (s != "") {
        ++p;
        info->builder2Data = BuilderData(s);
    }
    std::getline(*f.get(), s);
    if (s != "") {
        ++p;
        info->builder3Data = BuilderData(s);
    }
    if (p_size != p) throw std::invalid_argument("size not match");
    std::getline(*f.get(), s);
    size_t start = 0;
    size_t space;
    while(start < s.size()) {
        space = s.find(' ', start);
        info->board.emplace_back(std::stoi(s.substr(start, space-start)));
        start = space + 1;
    }
    std::getline(*f.get(), s);
    info->geese = std::stoi(s);
}
