#include "vertex.h"
#include <string>
#include <map>

const std::vector<std::string> PLAYER = {"BLUE", "RED", "ORANGE", "YELLOW"};

std::map<int, std::vector<int> > EdgeMap = adjacentEdge();

std::map<int, std::vector<int> > VertexMap = adjacentVertex();


Vertex::Vertex(int num): Num {num}, owner{-1}, 
AdjacentVertex{VertexMap[num]}, AdjacentEdge{EdgeMap[num]} {}

int Vertex::getNum() { return Num; }
std::vector<int> Vertex::getEdges() { return AdjacentEdge; }

int Vertex::getOwner(){
    return owner;
}

std::string Vertex::getType(){
    return type;
}

void Vertex::setOwner( int builder ){
    this->owner = builder;
}

void Vertex::setType( std::string type ){
    this->type = type;
}

void Vertex::ImproveResidence(){
    if (type == "basement"){
        type = "house";
    } else {
        type = "tower";
    }
}
