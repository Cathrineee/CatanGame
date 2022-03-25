#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <map>
#include <string>
#include "Display.h"
#include "Information.h"

class TextDisplay: public Display {

    // textlayout
    std::vector<std::vector<char>> layout;

public:
    TextDisplay(std::shared_ptr<Information> info, int p_size);
    virtual ~TextDisplay();

    // update information when a builder has built a residence
    void updateResidence(int vertex, int builder, std::string type, bool x) override;
    // update information when the builder has built a road
    void updateRoad(int edge, int builder, bool x) override;
    // update information when the builder has updated a geese
    void updateGeese(int tile) override;
    // update the resource information for the corresponding builder
    void updateResource(int builder, int resource, int num) override;
    // update the builder information when the builder sells its house for resources
    void sellHouse(int builder, int vertex, std::string type) override;

    // printBoard() prints the current board
    void printBoard() override;

    // printResidences(builder) prints the residences of
    //   the builder
    void printResidences(int builder) override;

    // printBuilders() prints the current status of the current builder
    void printBuilders() override;

    // CP_Basement(vertex) prints the building basement instructions of 
    //   computers
    void CP_Basement(int vertex) override;

    //  CP_Next() prints the computer's instruction -- "next"
    void CP_Next() override;
};



#endif
