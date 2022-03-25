#ifndef DISPLAY_H
#define DISPLAY_H

#include "Information.h"
#include <set>
#include <map>
#include <string>
#include <utility>
#include <memory>
#include <vector>

class Display {
    protected:
    // the number of current players
    int p_size;
    // the number of tile current geese is on
    int g;
    // map from builder's code to builder's name
    std::map<int, std::string> builders;
    // map from resource's code to resource's name
    std::map<int, std::string> resources;
    // map from builder's code to a vector of vectors:
    // 0. vector of the number of resources
    // 1. building points (vector with 1 element)
    // 2. vector of basement verticies
    // 3. vector of house verticies
    // 4. vector of tower verticies
    std::map<int, std::vector<std::vector<int>>> b_info;
    // map from tile's number to a pair of coordinates of its geese position
    std::map<int, std::pair<int, int>> geese_info;
    // map from tile's number to a pair of coordinates of its position
    std::map<int, std::pair<int, int>> tile_info;
    // map from vertex's num to a pair of coordinates
    std::map<int, std::pair<int, int>> v_info;
    // map from edge's num to a pair of coordinates
    std::map<int, std::pair<int, int>> e_info;
    // map from the code of a building to its type
    std::map<int, std::string> building;
    // maps the type of residence to the number of resources it needs
    std::map<char, std::vector<int>> payResources;

public:
    Display(std::shared_ptr<Information> info, int p_size);
    virtual ~Display();

    // output error message when the geese location is invalid
    void wrongGeeseLocation();
    // output message of how many resources the builder loses to the geese.
    void geeseHalfReport(int cur, int num, int energy, int brick, int glass, int heat, int wifi);
    // output the list of available builders the current player can choose from
    void availableBuilders(int cur, std::set<std::string> builder);
    // output the message of what resource the current builder steals from another player
    void stealMessage(int currentB, int b, int resource);
    // output the error message 
    void invalidFile();
    // output the error message when trying to build basement at an invalid address at the beginning of the game
    void rebuild(std::vector<int> vertex);
    // when the current builder cannot build residence/road at the chosen location
    void invalidBuild();
    // when the builder doesn not have enough resources to build the type of residence/road.
    // -1 - trade, 4 - raod, 1 - basement, 2 - house, 3 - tower
    // if builder is -1, then it is current builder.
    void noEnoughRes(int type, int builder = -1);
    // when the builder is trying to improve a tower
    void improveTower();
    // report message when no builders gained any resources
    void NoResourceMessage();
    // output the error message when the builder does not have residence at vertex v and tries to sell the house at v.
    void CannotSaleHouse(int v);

    // update information when a builder has built a residence
    virtual void updateResidence(int vertex, int builder, std::string type, bool x) = 0;
    // update information when the builder has built a road
    virtual void updateRoad(int edge, int builder, bool x) = 0;
    // update information when the builder has updated a geese
    virtual void updateGeese(int tile) = 0;
    // update the resource information for the corresponding builder
    virtual void updateResource(int builder, int resource, int num) = 0;
    // update the builder information when the builder sells its house for resources.
    virtual void sellHouse(int builder, int vertex, std::string type) = 0;

    // pure virtual function for printing the currnet board
    virtual void printBoard() = 0;
    // pure virtual function for printing the builder's residences.
    virtual void printResidences(int builder) = 0;
    // pure virtual function for printing the current builder's status
    virtual void printBuilders() = 0;

    // computer player's functios:
    // pure virtual function for printing that the computer has built a
    //   basement
    virtual void CP_Basement(int vertex) = 0;

    // pure virtual function for printing the computer instruction "next"
    virtual void CP_Next() = 0;

};


#endif
