#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "helper.h"

class Edge {
    int Num;
    bool Road;
    std::string Owner;
    std::vector<std::string> Adjacent;

    public:
    std::vector<int> AdjacentRoads;
    Edge(int Num);

     
    // checkAdjacent(b) checks if there is an Adjacent Residence or road build by a 
    //  same builder b   
    bool checkAdjacent( int b ); 

    // attach(o) attach an owner to the vector of Adjacent
    void attach(std::string o);

    void detach(std::string o);

    int getNum();
    bool ifRoad();
    std::string getOwner();

    // setRoad(owner) set an edge to a road (modifies the owner and changes the state)
    void setRoad(std::string owner);
};

std::ostream & operator<<(std::ostream &out, const Edge &e);

#endif
