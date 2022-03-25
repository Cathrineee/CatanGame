#include "edge.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::map<int, std::vector<int>> EdgeMap1 = edgeToEdge();

// constructor
Edge::Edge(int Num) : Num{Num},
 Road{false}, Owner{-1}, AdjacentRoads{EdgeMap1[Num]}{}

int Edge::getNum() { return Num; }

bool Edge::ifRoad() { return Road; }

std::string Edge::getOwner() { return Owner; }

void Edge::setRoad(std::string o)
{
    Road = true;
    Owner = o;
}

bool Edge::checkAdjacent( int b ){
    std::vector<std::string> bdList = {"Blue", "Red", "Orange",
    "Yellow"};
   if (std::count(Adjacent.begin(), Adjacent.end(), bdList.at(b))){
       return true;
   } else {
       return false;
   }  
}

void Edge::attach(std::string o){
    Adjacent.emplace_back(o);
}

void Edge::detach(std::string o){
    int i = 0;
    bool judge =  false;
    for(auto adj: Adjacent){
      if((adj == o) && (judge == false)){  
        Adjacent.erase(Adjacent.begin()+i);  
        judge = true;
      }
      ++i;  
    }
}
