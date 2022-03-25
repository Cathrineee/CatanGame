#ifndef VERTEX_H
#define VERTEX_H

#include "residence.h"
#include "edge.h"
#include <vector>
#include <iostream>
#include <memory>
#include "helper.h"


class Vertex {
    int Num;
    int owner;
    std::string type;

    public:
    std::vector<int> AdjacentVertex;
    std::vector<int> AdjacentEdge;
    Vertex(int num);

    // getOwner() returns the owner of the vertex
    //  -1 if there is no owner for this vertex 
    int getOwner();
    
    // getNum() returns the number of the vertex
    int getNum();

    // getEdges() returns the edges of the vertex
    std::vector<int> getEdges();

    // getType() returns the type of the residence of this vertex
    std::string getType();

    // setOwner(builder) set the owner of a residence to builder
    void setOwner( int builder );

    // setType(type) set the type of a residence to builder
    void setType( std::string type );

    // ImproveResidence set the type of the residence 
    void ImproveResidence();
};

#endif
