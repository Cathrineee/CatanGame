#ifndef CUSTOMIZEDLEVEL_H
#define CUSTOMIZEDLEVEL_H

#include "InitialLevel.h"
#include <memory>
#include <iostream>

class CustomizedLevel : public Level {
    std::shared_ptr<std::istream> f;
    void updateInfo() override;
    
    public: 
    CustomizedLevel(int p_size, std::shared_ptr<std::istream> f);
    virtual ~CustomizedLevel();
};

#endif
