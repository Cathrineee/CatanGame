#ifndef INITIALLEVEL_H
#define INITIALLEVEL_H

#include "board.h"
#include "Information.h"
#include "BuilderData.h"
#include <vector>
#include <memory>
#include <iostream>

class Level {
    virtual void updateInfo() = 0;

    protected:
    std::shared_ptr<Information> info;
    int p_size;

    public:
    Level(int p);
    virtual ~Level();
    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Board> restartBoard();
};


#endif
