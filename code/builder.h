#ifndef BUILDER_H
#define BUILDER_H
#include "residence.h"
#include <memory>
#include <vector>

class Builder {
   std::string Name;
   int ID;
   int Point;
   std::vector<int> Road;
   std::vector<std::shared_ptr<Residence>> Residences;  
   int ResEnergyNum;
   int ResBrickNum; 
   int ResGlassNum;
   int ResHeatNum;
   int ResWifiNum;

   public:  
   // constructor
   Builder( std::string Name, int ID , int ResEnergyNum = 0, int ResBrickNum = 0, 
   int ResGlassNum = 0, int ResHeatNum = 0, int ResWifiNum = 0);

   // getEnergy() returns the number of Energy
   int getEnergy();

   // getBrick() returns the number of Brick
   int getBrick();

   // getGlass() returns the number of Glass
   int getGlass();

   // getHeat() returns the number of Heat
   int getHeat();

   // getWifi() returns the number of Wifi
   int getWifi();

   // getPoint() returns the number of Point
   int getPoint();

   // getID() returns the ID
   int getID();

   // getRoad() returns all the roads that builders owe
   std::vector<int> getRoad();

   // getResidences() returns the residences that builders build
   std::vector<std::shared_ptr<Residence>> getResidences();

   // checkBuildBasement() checks if the builder has enough resources to build a basement
   bool checkBuildBasement();

   // buildBasement builds a basement at vertex v, helps to subtract each resource of 
   //    current builder and update the point
   void buildBasement( int vertex, bool first );

   // checkImprovement(vertex) checks if the builder has enough resources to update its
   //  residence at vertex v
   bool checkImprovement( int v );

   // ImproveResidence(v) improves a residence at vertex v, helps to subtract each 
   //    resource of current builder and update the point
   void ImproveResidence( int v, bool first);

   // checkRoad() checks if the builder has enough resource to builde 
   bool checkRoad();

   // PayRoad(edgeNum) helps to subtract each resource of current builder and build
   //  road
   void BuildRoad(int edgeNum, bool first);

   // GetResource(res, num) updates the resource of the current builder
   //    when the builder get a resource
   void getResource( int res, int num );

   // GetResource(res, num) updates the resource of the current builder
   //    when the builder loses a resource
   void loseResource( int res, int num = 1);

   // CheckTrade(take, num) checks whether the builder have enough resource
   // to trade
   bool CheckTrade(int take, int num = 1 );

   // trade(give, take) updates the number of resources of this client
   //   after the trade
   void trade( int give, int take); 

   // calculateResource() calculates the number of resources of the builder
   int calculateResource();

   // HalfResource(int seed) makes the number of resource the half of that 
   void HalfResource(int seed);

   // GetStolen(int seed) subtracts one of the resource that this builder has. The
   //  probability of stealing/losing each type of resource is the number of
   //  the resource the builder being stolen from has, divided by the total 
   //  number of resources the builder being stolen from has. 
   //  It returns the resource which the builder got stolen
   int GetStolen(int seed);

   // addResource(resource, num, v) returns a vector adding num resource from
   //    vector v.
   std::vector<int> addResource(int resource,int num, std::vector<int> v);

   // demolition(vertex) demolites builder's house on vertex
   //   requires: vertex is valid
   void demolition(int vertex);

   // SaleBasement(vertex) helps t builder sales the basement of
   //    the current builder on vertex 
   //    requires: vertex is valid
   void SaleBasement(int vertex);

   // SaleHouse(vertex) helps t builder sales the house of
   //    the current builder on vertex
   //    requires: vertex is valid
   void SaleHouse(int vertex);

   // SaleTower(vertex) helps t builder sales the tower of
   //    the current builder on vertex
   //    requires: vertex is valid
   void SaleTower(int vertex);
};

#endif
