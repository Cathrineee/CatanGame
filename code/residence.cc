#include <iostream>
#include "residence.h"

Residence::Residence(std::string type, int vertex):
type {type}, vertex{vertex} {}

int Residence::getVertex(){
    return vertex;
}

void Residence::UpdateResidence(){
    if (type == "basement"){
        type = "house";
    } else {
        type = "tower";
    }
}

int Residence::improveType(){
    if (type == "basement"){
        return 1;
    } else {
        return 2;
    }
}

char Residence::getPrintType(){
    if(type == "basement") return 'B';
    else if (type == "house") return 'H';
    else return 'T';
}
