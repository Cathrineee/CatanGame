#include "RandomLevel.h"
#include "Information.h"
#include <algorithm>
#include <vector>
#include <string>

RandomLevel::RandomLevel(int p_size, int seed): Level(p_size) {
    rng.seed(seed);
}
RandomLevel::~RandomLevel() {}

void RandomLevel::updateInfo() {
    std::vector<int> tile{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5};
    std::vector<int> val{2};
    std::vector<int> threeSix{3, 4, 5, 6};
    std::vector<int> eightEleven{8, 9, 10, 11};
    std::vector<int> board_layout;

    std::shuffle(tile.begin(), tile.end(), rng);
    for (int i = 1; i < 9; ++i) {
        std::shuffle(threeSix.begin(), threeSix.end(), rng);
        val.emplace_back(threeSix.front());
    }
    for (int i = 9; i < 17; ++i) {
        std::shuffle(eightEleven.begin(), eightEleven.end(), rng);
        val.emplace_back(eightEleven.front());
    }
    val.emplace_back(12);
    auto pos = std::find(tile.begin(), tile.end(), 5);
    if (pos == tile.end())
        val.emplace_back(7);
    else
        val.insert(val.begin() + (pos - tile.begin()), 7);

    info->CurTurn = -1;
    info->builder0Data = BuilderData();
    info->builder1Data = BuilderData();
    info->builder2Data = BuilderData();
    info->builder3Data = BuilderData();
    for (int i = 0; i < 19; ++i) {
        board_layout.emplace_back(tile[i]);
        board_layout.emplace_back(val[i]);
    }
    info->board = board_layout;
    info->geese = -1;
}

