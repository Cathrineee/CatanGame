#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>


class Residence
{
    std::string type;
    int vertex;

public:
    Residence(std::string type, int vertex);

    // getVertex() returns the vertex of residence
    int getVertex();

    // UpdateResidence() updates the type of the residence
    void UpdateResidence();

    // improvetype() returns 1 if we want to upgrade from basement to house
    //   It returns 2 if we want to upgrade from house to tower
    int improveType();

    // getPrintType() returns the printing type of the current residence
    char getPrintType();
};

#endif
