#include "CustomizedLevel.h"
#include "Information.h"
#include <string>
#include <stdexcept>

CustomizedLevel::CustomizedLevel(int p_size, std::shared_ptr<std::istream> f): Level(p_size), f{f} {}
CustomizedLevel::~CustomizedLevel() {}

void CustomizedLevel::updateInfo() {
    std::string s;
    info->CurTurn = -1;
    info->builder0Data = BuilderData();
    info->builder1Data = BuilderData();
    info->builder2Data = BuilderData();
    info->builder3Data = BuilderData();
    std::getline(*f.get(), s);
    int num = 0;
    size_t start = 0;
    size_t space;
    while (start < s.size()) {
        space = s.find(' ', start);
        if (space == std::string::npos) throw std::invalid_argument("invalid format");
        info->board.emplace_back(std::stoi(s.substr(start, space - start)));
        start = space + 1;
        ++num;
    }
    if (num != 38) throw std::invalid_argument(std::to_string(num));
    info->geese = -1;
}

