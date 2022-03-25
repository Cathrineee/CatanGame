#ifndef PREVIOUSLEVEL_H
#define PREVIOUSLEVEL_H

#include "InitialLevel.h"
#include <memory>
#include <iostream>

class PreviousLevel : public Level {
    std::shared_ptr<std::istream> f;
    void updateInfo() override;

    public:
    PreviousLevel(int p_size, std::shared_ptr<std::istream> f);
    virtual ~PreviousLevel();
};


#endif
