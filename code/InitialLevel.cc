#include "InitialLevel.h"

Level::Level(int p_size): info{ new Information() }, p_size{p_size} {}
Level::~Level() {}

std::shared_ptr<Board> Level::getBoard() {
    updateInfo();
    return std::make_shared<Board>(info, p_size);
}

std::shared_ptr<Board> Level::restartBoard() {
    return std::make_shared<Board>(info, p_size);
}
