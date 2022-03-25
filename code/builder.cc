#include <iostream>
#include "builder.h"
#include <random>
#include <algorithm>

Builder::Builder( std::string Name, int ID , int ResEnergyNum, int ResBrickNum, int ResGlassNum, 
   int ResHeatNum, int ResWifiNum): Name{Name}, ID {ID},
   ResEnergyNum {ResEnergyNum},
   ResBrickNum{ResBrickNum}, ResGlassNum{ResGlassNum}, ResHeatNum{ResHeatNum},
   ResWifiNum{ResWifiNum} {}


int Builder::getEnergy(){
    return ResEnergyNum;
}

int Builder::getBrick(){
    return ResBrickNum;
}

int Builder::getGlass(){
    return ResGlassNum;
}

int Builder::getHeat(){
    return ResHeatNum;
}   

int Builder::getWifi(){
    return ResWifiNum;
}

int Builder::getPoint(){
    return Point;
}

std::vector<std::shared_ptr<Residence>> 
Builder::getResidences(){
    return Residences;
}

std::vector<int> Builder::getRoad(){
    return Road;
}

bool Builder::checkBuildBasement(){
    if ((ResBrickNum >= 1) && (ResEnergyNum >= 1) &&
        (ResGlassNum >= 1)) {
            return true;
    } else {
        return false;
    }
}

void Builder::buildBasement(int vertex, bool first){
    Point += 1;
    if( first == false){
        ResBrickNum -= 1;
        ResEnergyNum -= 1;
        ResGlassNum -= 1;
        ResWifiNum -= 1;
    }
    auto res = std::make_shared<Residence>("basement", vertex);
    Residences.emplace_back(res);
}

bool Builder::checkImprovement(int v){
   for( auto res: Residences ){
       if(res->getVertex() == v){
           if(res->improveType() == 1){
              if((ResGlassNum >= 2) &&
                 (ResHeatNum >= 3)){
                 return true;            
              }  else {
                  return false;
              }
           } else {
              if((ResBrickNum >= 3) &&
                 (ResEnergyNum >= 2) &&
                 (ResGlassNum >= 2) &&
                 (ResWifiNum >= 1) &&
                 (ResHeatNum >= 2)){
                     return true;
                } else {
                    return false;
                } 
           }
       }
    }
    return false;  
}

void Builder::ImproveResidence(int v, bool first){
   Point += 1;
   for( auto res: Residences ){
       if(res->getVertex() == v){
           if (first == false){
               if(res->improveType() == 1){
                   ResGlassNum -= 2;
                   ResHeatNum -= 3;            
                } else {
                  ResBrickNum -= 3;
                  ResEnergyNum -= 2;
                  ResGlassNum -= 2;
                  ResWifiNum -= 1;
                  ResHeatNum -= 2;  
              }
            }
            res->UpdateResidence();
           }
       }
}  

bool Builder::checkRoad(){
    if((ResHeatNum >= 1) && (ResWifiNum >= 1)){
        return true;
    }
    return false;
}

void Builder::BuildRoad(int edgeNum, bool first){
    if (first == false){
        ResHeatNum -= 1;
        ResWifiNum -= 1;
    }
    Road.emplace_back(edgeNum);
}

void Builder::getResource( int res, int num ){
    if(res == 0){
        ResBrickNum += num;
    } else if(res == 1){
        ResEnergyNum += num;
    } else if(res == 2){
        ResGlassNum += num;
    } else if(res == 3){
        ResHeatNum += num;
    } else {
        ResWifiNum += num;
    }
}

void Builder::loseResource( int res, int num ){
    if(res == 0){
        ResBrickNum -= num;
    } else if(res == 1){
        ResEnergyNum -= num;
    } else if(res == 2){
        ResGlassNum -= num;
    } else if(res == 3){
        ResHeatNum -= num;
    } else {
        ResWifiNum -= num;
    }
}

bool checkBiggerThanNum(int resource, int num){
    if(resource >= num ) {
        return true;
    } else {
        return false;
    }
}

bool Builder::CheckTrade(int take, int num ){
    if(take == 0){
        return checkBiggerThanNum(ResBrickNum, num);
    } else if(take == 1){
        return checkBiggerThanNum(ResEnergyNum, num);
    } else if(take == 2){
        return checkBiggerThanNum(ResGlassNum, num);
    } else if(take == 3){
        return checkBiggerThanNum(ResHeatNum, num);
    } else {
        return checkBiggerThanNum(ResWifiNum, num);
    }
}

void Builder::trade(int give, int take){
    getResource(take, 1);
    loseResource(give, 1);
}

int Builder::calculateResource(){
    return (ResEnergyNum + ResWifiNum + ResBrickNum +
    ResGlassNum + ResHeatNum);
}

void Builder::HalfResource(int seed){
    std::vector<int> resource_vector;
    int sum = (ResEnergyNum + ResWifiNum + ResBrickNum +
    ResGlassNum + ResHeatNum);
    resource_vector = addResource(1, ResEnergyNum, 
    resource_vector);
    resource_vector = addResource(0, ResBrickNum, 
    resource_vector);
    resource_vector = addResource(2, ResGlassNum, 
    resource_vector);
    resource_vector = addResource(3, ResHeatNum, 
    resource_vector);
    resource_vector = addResource(4, ResWifiNum, 
    resource_vector);
    unsigned int se = seed;
    std::default_random_engine rng {se};
    std::shuffle(resource_vector.begin(), 
    resource_vector.end(), rng);
    ResBrickNum = 0;
    ResEnergyNum = 0;
    ResGlassNum = 0;
    ResHeatNum = 0;
    ResWifiNum = 0;
    for(int i = 0; i < sum/2; ++i){
        if(resource_vector.at(i) == 0){
        ResBrickNum += 1;
        } else if(resource_vector.at(i) == 1){
            ResEnergyNum += 1;
        } else if(resource_vector.at(i) == 2){
            ResGlassNum += 1;
        } else if(resource_vector.at(i) == 3){
            ResHeatNum += 1;
        } else {
            ResWifiNum += 1;
        }
    }
}

std::vector<int> Builder::addResource(int resource,
int num, std::vector<int> v){
   for(int i = 0; i < num; ++i){
        v.emplace_back(resource);
    }
    return v;
}

int Builder::GetStolen(int seed){
    std::vector<int> resource_vector;
    resource_vector = addResource(1, ResEnergyNum, 
    resource_vector);
    resource_vector = addResource(0, ResBrickNum, 
    resource_vector);
    resource_vector = addResource(2, ResGlassNum, 
    resource_vector);
    resource_vector = addResource(3, ResHeatNum, 
    resource_vector);
    resource_vector = addResource(4, ResWifiNum, 
    resource_vector);
    unsigned se = seed;
    std::default_random_engine rng {se};
    std::shuffle(resource_vector.begin(), 
    resource_vector.end(), rng);
    int res = resource_vector.at(0);
    if(res == 0){
        ResBrickNum -= 1;
    } else if(res == 1){
        ResEnergyNum -= 1;
    } else if(res == 2){
        ResGlassNum -= 1;
    } else if(res == 3){
        ResHeatNum -= 1;
    } else {
        ResWifiNum -= 1;
    }
    return res;
}

int Builder::getID(){
    return ID;
}

void Builder::demolition(int vertex){
  int i = 0;
  for(auto bas: Residences){
        if(bas->getVertex() == vertex){
            Residences.erase(Residences.begin()+i);
            return;
        }
        i += 1;
    }
}

void Builder::SaleBasement(int vertex){
    ResBrickNum += 1;
    ResEnergyNum += 1;
    Point -= 1;
    demolition(vertex);
}

void Builder::SaleHouse(int vertex){
    ResGlassNum += 1;
    ResHeatNum += 1;
    ResBrickNum += 1;
    ResEnergyNum += 1;
    Point -= 2;
    demolition(vertex);
}

void Builder::SaleTower(int vertex){
    ResGlassNum += 2;
    ResHeatNum += 2;
    ResBrickNum += 2;
    ResEnergyNum += 2;
    ResWifiNum += 1;
    Point -= 3;
    demolition(vertex);
}
