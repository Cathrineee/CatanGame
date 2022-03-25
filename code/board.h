#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "Information.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "builder.h"
#include "Display.h"
#include "BuilderData.h"
#include <map>
#include <set>
#include <fstream>
#include <memory>
#include <string>

class Board {
    std::vector<std::shared_ptr<Tile>> Tiles;
    std::vector<std::shared_ptr<Edge>> Edges;
    std::vector<std::shared_ptr<Vertex>> Vertexes;
    std::vector<std::shared_ptr<Builder>> Builders;
    std::shared_ptr<Display> display;
    int CurrentTurn;
    int GeeseLocation;


    public:
    // Constructor's helper function
    // InitializeBuildersInfo(name, id, bd) initializes the buidler information
    void InitializeBuildersInfo(std::string name, int id, 
     BuilderData bd );

    // Consturctor's helper function
    // check_ValidEdge(n) checks if the edge n is a valid edge
    void check_ValidEdge(int n); 

    // Consturctor's helper function
    // check_ValidEdge(n) checks if the edge n is a valid edge
    void check_ValidVertex(int n); 

    // constructor
    Board( std::shared_ptr<Information> info, int builderNum = 4 );

    // SaveBoard(file) saves the board information to file-file
    void SavedBoard( std::string file );

    // BuildBasement(builder, vertex, first) builds a basement.
    //  (Boolean first will judge if this is the first time building basement)
    //   It returns true if the current player successfully builds the basement 
    bool BuildBasement( int builder, int vertex, bool first = false);

    // UpdatedResidence updates residence for builder at vertex. It returns -1 if successful, 0 if residence is 
    //   invalid, 1-2 if the current builder does not have enough resources, 1 if current residence is a basement,
    //    2 if current residence is a house and 3 if current residence is a tower 
    //   (Boolean will judge if this is the first time)
    void UpdateResidence( int builder, int vertex, bool first = false );

    // BuildRoad builds a road for builder at vertex. It returns -1 if do not have enough resources, 0 if road is
    //   invalid and 1 if successful
    //   (Boolean will judge if this is the first time)
    void BuildRoad( int builder, int edgeNum, bool first = false );

    // next(builderNum) updates the current turm 
    void next(int builderNum = 4);

    // printBuilder() prints the builders' information 
    void printBuilder();

    // printResidences() prints the residences of the current builder
    void printResidences();

    // gainResource(rollnum) helps the current player gain resources based on roll number rollnum
    void gainResource(int rollnum);

    // Trade(builder, give, take) does trade between current turn builder and builder.
    void Trade( int builder, int give, int take );

    // GeeseHalf(seed) lets any builder with 10 or more resource wil automatically lose half
    //   of their resources(rounded down) to the geese and call Display to print the message
    void GeeseHalf(int seed);

    // UpdateGeese(NewLocation) updates the location of the geese and call Dispaly to print
    //   available builders. It returns available builders. (If newLocation is equal to CurrentLocation,
    //   call Display to print error messages)
    std::set<std::string> UpdateGeese( int NewLocation);
    
    // StealBuilder(b, seed) helps the current player to steal resource from b and call Display to print 
    //   the stealing message
    // requires: b must be valid
    void StealBuilder(int b, int seed);

    // win(builder) determines whether this builder wins or not
    bool win( int builder );

    // printBoard() calls display and prints the whole board
    void printBoard();

    // ExistedResidences() return a vector of vertexes containing a residence
    std::vector<int> ExistedResidences();

    // GetCurrentTurn() returns current turn
    int GetCurrentTurn();

    // The Function of Bank: ExchangeResource(builder, give, take) exchanges resources. 
    //   Current builder gets one resource-take and gives four resource-give
    //   4 => 1
    void ExchangeResource(int give, int take);
    
    // The Function of Bank: SaleHouse(builder, vertex) sales the house of the current builder, 
    //    the current builder gets resources and decreases the building point.
    //    basement: 1 brick, 1 energy, 1 glass, 1 wifi => 1 brick, 1 energy
    //    house: 2 glass, 3 heat => 1 glass, 1 heat, 1 brick, 1 energy
    //    tower: 3 brick, 2 energy, 2 glass, 1 wifi, 2 heat => 2 glass, 2 heat, 2 brick, 2 energy, 1 wifi
    void SaleHouse(int vertex);

    // ComputerPlayerDecision(initialize) helps computer to do the decision
    //   (i.e prints the computer desicion in to a file called 
    //    "computerplayer.txt")
    void ComputerPlayerDecision(bool initialize = false);
};


#endif
