#include "board.h"
#include "textDisplay.h"

void Board::InitializeBuildersInfo(std::string name, int id, 
BuilderData bd){
    auto eachBuilder = std::make_shared<Builder>(name, id, bd.numEnergies,
   bd.numBricks, bd.numGlass, bd.numHeat, bd.numWifi);
    Builders.push_back(eachBuilder);
}

void Board::check_ValidEdge(int n){
    if((n<0)||(n>71)){
        display->invalidFile();
        exit(1);
    }
}

void Board::check_ValidVertex(int n){
    if((n<0)||(n>53)){
        display->invalidFile();
        exit(1);
    }
}

Board::Board( std::shared_ptr<Information> info, int builderNum) {
   std::vector<BuilderData> BD{info->builder0Data, info->builder1Data,
   info->builder2Data, info->builder3Data };
   std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
   // Initialize current turn
   CurrentTurn = info->CurTurn;

   // update Geese Location
   GeeseLocation = info->geese;

   // create display and assign
   this->display = std::make_shared<TextDisplay>(info, builderNum);
   // notify display that geese's location has been changed
   display->updateGeese(GeeseLocation);

   // Initialize Edges
   for(int i = 0; i < 72; ++i){
       auto eachEdge = std::make_shared<Edge>(i);
       Edges.push_back(eachEdge);
    }

   // Initialize Vertexes
   for(int i = 0; i < 54; ++i){
       auto eachVertex = std::make_shared<Vertex>(i);
       Vertexes.push_back(eachVertex);
   }

   // Initialize Tiles
   //   2*i is resource, 2*i+1 is value
   for(int i = 0; i < 19; ++i) {
       if((info->board.at(2*i+1)<2) || 
       (info->board.at(2*i+1)>12) ||
       (info->board.at(2*i)<0) ||
       (info->board.at(2*i)>5)){
           display->invalidFile();
           exit(1);
       }
       if(info->board.at(2*i) == 5) {
         if(info->board.at(2*i+1) != 7){
           display->invalidFile();
           exit(1);
         }   
       }
       auto eachTile = std::make_shared<Tile>(i, info->board.at(2*i+1) 
       ,info->board.at(2*i));
       Tiles.push_back(eachTile);
    }

   // builder information update
   for(int i = 0; i < builderNum; ++i){
       // initialize builder information
       InitializeBuildersInfo(BuilderInformation[i], i, BD.at(i));

       // build road
       for( auto edgeNum: BD.at(i).road){
           check_ValidEdge(edgeNum);
           BuildRoad(i, edgeNum, true);
        }

       // build basement
       for( auto vertexNum: BD.at(i).basement){
           check_ValidVertex(vertexNum);
           BuildBasement(i, vertexNum, true);
       }

       // build house
       for( auto vertexNum: BD.at(i).house){
           check_ValidVertex(vertexNum);
           BuildBasement(i, vertexNum, true);
           UpdateResidence(i, vertexNum, true);
       }

       // build tower
       for( auto vertexNum: BD.at(i).tower){
           check_ValidVertex(vertexNum);
           BuildBasement(i, vertexNum, true);
           UpdateResidence(i, vertexNum, true);
           UpdateResidence(i, vertexNum, true);
       }
   }
}

void Board::SavedBoard( std::string file ){
   std::ofstream outfile{file};
   // <curTurn>
   outfile << std::to_string(CurrentTurn) << std::endl;
   // <builderData>
   for(auto b: Builders){
       outfile << b->getBrick() << " " << b->getEnergy() << " " << b->getGlass()
       << " " << b->getHeat() << " " << b->getWifi() << " ";
       outfile << "r" << " ";
       for(auto r: b->getRoad()){
           outfile << r << " ";
       }
       outfile << "h" << " ";
       for(auto res: b->getResidences()) {
           outfile << res->getVertex() << " " << 
           res->getPrintType() << " ";
       } 
       outfile << std::endl;
   }

   // save empty players 
   int i = Builders.size();
   while(i < 4){
       outfile << std::endl;
       ++i;
   }

   // <board>
   for(auto t: Tiles){
       outfile << t->getResource() << " " << t->getValue() << " ";
   } 
   outfile << std::endl;
   // <geese>
   outfile << GeeseLocation << std::endl;
}


bool Board::BuildBasement( int builder, int vertex, bool first ){
    std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
    
    // vertex out of range
    if((vertex < 0) || (vertex > 53)) {
        display->invalidBuild();
        return false;
    }

    // if the chosen vertex is a residence
    if ( Vertexes.at(vertex)->getOwner() != -1 ) {
        if( first == false ){
           display->invalidBuild();
        } else {
            display->rebuild(ExistedResidences());     
        }
        return false;
    }
    

    // if the chosen vertex is adjacent to a vertex with an existing 
    //   residence
    for( auto v: Vertexes.at(vertex)->AdjacentVertex ){
        if(v >= 0){
            if (Vertexes.at(v)->getOwner()!=-1){
                if ( first == true ){
                    display->rebuild(ExistedResidences());
                } else {
                    display->invalidBuild();
                }
                return false;
            }
        }
    }

    if(!first){    
        // check if the chosen vertex has an adjacent road
        bool judge = false;
        for( auto e: Vertexes.at(vertex)->AdjacentEdge ){
            if(e >= 0){
                if((Edges.at(e)->ifRoad() == true) &&
                   (Edges.at(e)->getOwner()==
                   BuilderInformation[builder])){
                    judge = true;
                }
            }
        }
        if(judge == false){
            display->invalidBuild();
            return false;
        }
        
        // if the builder does not have enough resource to build the basement
        if ( Builders.at(builder)->checkBuildBasement() == false ){
            display->noEnoughRes(0);
            return false;
        }
    }

    // successfully build the basement
    Builders.at(builder)->buildBasement( vertex, first );
    Vertexes.at(vertex)->setOwner( builder );
    Vertexes.at(vertex)->setType( "basement" );

    // notify all the adjacent edges
    for( auto e: Vertexes.at(vertex)->AdjacentEdge ){  // e is the number of edge
      if((e >= 0) && (e <= 71)){
        Edges.at(e)->attach(BuilderInformation[builder]);
      }
    }

    display->updateResidence(vertex, builder, "basement", first);
    return true;
}

void Board::UpdateResidence( int builder, int vertex, bool first ){
    // vertex out of range
    if((vertex < 0) || (vertex > 53)) {
        display->invalidBuild();
        return;
    }

    std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
    // return 0 if residence is other
    if (Vertexes.at(vertex)->getOwner() != builder ){
        display->invalidBuild();
        return; 
    }

    if(first == false){
        // return 3 if current residence is a tower
        if (Vertexes.at(vertex)->getType() == "tower") {
            display->improveTower();
            return;
        }

        // return 1-2 if the builder does not have enough resources to update
        if ( (first == false) &&
             (Builders.at(builder)->checkImprovement( vertex ) == false) ){
            if ( Vertexes.at(vertex)->getType() == "basement" ){
                display->noEnoughRes(2);
                return;
            } else {
                display->noEnoughRes(3);
                return;
            }
        }
    }

    std::string tpe;
    if ( Vertexes.at(vertex)->getType() == "basement" ){
        tpe = "house";    
    } else {
        tpe = "tower";
    }

    // return -1 if successfully improve
    Builders.at(builder)->ImproveResidence( vertex, first );
    Vertexes.at(vertex)->ImproveResidence();
    display->updateResidence(vertex, builder, tpe, first);
}

void Board::BuildRoad( int builder, int edgeNum, bool first ){
    std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
    
    // edge out of range
    if((edgeNum < 0) || (edgeNum > 71)) {
        display->invalidBuild();
        return;
    }

    if (first == false){
        check_ValidEdge(edgeNum);
        // return -1 if the builder does not have enough resources
        if ( (first == false) && (Builders.at(builder)->checkRoad() == false )){
            display->noEnoughRes(4);
            return;
        }

        // return 0 if the road is invalid 
        if ((!Edges.at(edgeNum)->checkAdjacent(builder)) ||
            (Edges.at(edgeNum)->ifRoad())){
            display->invalidBuild();
            return;    
        }
    }

    // return 1 if the builder successfully builds the road
    Builders.at(builder)->BuildRoad(edgeNum, first);
    Edges.at(edgeNum)->setRoad(BuilderInformation[builder]);
    // notify all the adjacent road
    for( auto e: Edges.at(edgeNum)->AdjacentRoads ) { // e is the number of adjacent edges
       Edges.at(e)->attach(BuilderInformation[builder]);
    }
    display->updateRoad(edgeNum, builder, first);
}

void Board::next(int builderNum){
    if( CurrentTurn == builderNum - 1 ){
        CurrentTurn = 0;
    } else {
       CurrentTurn += 1;
    }
}

void Board::printBuilder(){
   display->printBuilders(); 
}
 
void Board::printResidences(){
    display->printResidences(CurrentTurn);
}

void Board::gainResource( int rollnum ) {
   bool judge = false;
   for( auto t: Tiles ) {
       if ( t->getValue() == rollnum ){
           for(auto v: t->Vertexes){
               int num = 0;
               if (Vertexes.at(v)->getOwner() != -1){
                    if(Vertexes.at(v)->getType() == "basement") num += 1;
                    if(Vertexes.at(v)->getType() == "house") num += 2;
                    if(Vertexes.at(v)->getType() == "tower") num += 3;
                    judge = true;
               }
               if(num!=0){
                    Builders.at(Vertexes.at(v)->getOwner())->getResource(t->getResource(), num);
                    display->updateResource(Vertexes.at(v)->getOwner(), t->getResource(), num);
               }
           }
        }
    }
   if(judge == false) display->NoResourceMessage();
}

void Board::Trade( int builder, int give, int take ){
    if( Builders.at(CurrentTurn)->CheckTrade(give) &&
        Builders.at(builder)->CheckTrade(take) ) {
            Builders.at(CurrentTurn)->trade(give, take);
            Builders.at(builder)->trade(take, give);
            display->updateResource(CurrentTurn, give, -1);
            display->updateResource(CurrentTurn, take, 1);
            display->updateResource(builder, give, 1);
            display->updateResource(builder, take, -1);
            return;
    }
    if(!Builders.at(CurrentTurn)->CheckTrade(give)){
        display->noEnoughRes(-1);
        return;
    } else {
        display->noEnoughRes(-1, builder);
        return;
    }
}

void Board::GeeseHalf(int seed){
    // Any builders with 10 or more resource will automatically lose half of their resource
    for( auto b: Builders ){
        int num = b->calculateResource();
        if (num >= 10){
            int energy = b->getEnergy();
            int brick = b->getBrick();
            int glass = b->getGlass();
            int heat = b->getHeat();
            int wifi = b->getWifi();
            b->HalfResource(seed);
            int NewEnergy = b->getEnergy();
            int NewBrick = b->getBrick();
            int NewGlass = b->getGlass();
            int NewHeat = b->getHeat();
            int NewWifi = b->getWifi();
            display->geeseHalfReport(b->getID(), num - num / 2, energy - NewEnergy, brick - NewBrick,
            glass - NewGlass, heat - NewHeat, wifi - NewWifi);
        }
    }
}

std::set<std::string> Board::UpdateGeese(int NewLocation){
    std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
    std::set<std::string> buildernames;
    if ((NewLocation < 0) || (NewLocation > 18) ||
        (NewLocation == GeeseLocation)){
        display->wrongGeeseLocation();
        buildernames.insert("?");
    } else {
        GeeseLocation = NewLocation;
        for(auto v: Tiles.at(NewLocation)->Vertexes ){
            if ( (Vertexes.at(v)->getOwner() != -1) &&
                (Builders.at(Vertexes.at(v)->getOwner())->calculateResource() > 0) &&
                (CurrentTurn != Vertexes.at(v)->getOwner())){
                buildernames.insert(BuilderInformation[Vertexes.at(v)->getOwner()]);
            }
        }
        display->availableBuilders(CurrentTurn, buildernames);
        display->updateGeese(NewLocation);
    }
    return buildernames;
}

void Board::StealBuilder(int b, int seed){
    int res = Builders.at(b)->GetStolen(seed);
    Builders.at(CurrentTurn)->getResource(res, 1);
    display->stealMessage(CurrentTurn, b, res);
}

bool Board::win(int builder){
    int point = Builders.at(CurrentTurn)->getPoint();
    if (point >= 10){
        return true;
    } else {
        return false;
    }
}

void Board::printBoard(){
    display->printBoard();
}

std::vector<int> Board::ExistedResidences(){
    std::vector<int> existedList;
    for(auto v: Vertexes){
        if(v->getOwner()!= -1){
            existedList.emplace_back(v->getNum());
        }
    }
    return existedList;
}

int Board::GetCurrentTurn(){
    return CurrentTurn;
}

void Board::ExchangeResource(int give, int take){
  if (Builders.at(CurrentTurn)->CheckTrade(give, 4)){
      Builders.at(CurrentTurn)->loseResource(give, 4);
      display->updateResource(CurrentTurn, give, -4);
      display->updateResource(CurrentTurn, take, 1);
  } else {
      display->noEnoughRes(give, 5);
      return;
  }
  Builders.at(CurrentTurn)->getResource(take, 1);  
}

void Board::SaleHouse(int vertex){
  if((vertex<0)||(vertex>53)){
        display->CannotSaleHouse(vertex);
        return;
  }
  std::map<int, std::string> BuilderInformation = createBuilderInfoMap();
  // if the current builder can sale his house  
  if (Vertexes.at(vertex)->getOwner() == CurrentTurn) {
      if (Vertexes.at(vertex)->getType() == "basement") {
          // Demolition
          Builders.at(CurrentTurn)->SaleBasement(vertex);
      } else if (Vertexes.at(vertex)->getType() == "house") {
          // Demolition
          Builders.at(CurrentTurn)->SaleHouse(vertex);
      } else {
          // Demolition
          Builders.at(CurrentTurn)->SaleTower(vertex);
      }
    Vertexes.at(vertex)->setOwner(-1);
    display->sellHouse(CurrentTurn, vertex, Vertexes.at(vertex)->getType());
    // notify all adjacent Edges
    for(auto adjEdge: Vertexes.at(vertex)->getEdges()){
       if((adjEdge >= 0) && (adjEdge <= 71)){ 
        Edges.at(adjEdge)->detach(BuilderInformation[CurrentTurn]); 
       }
    }
  } else {
    display->CannotSaleHouse(vertex);
  }
}

void Board::ComputerPlayerDecision(bool initialize){
    std::ofstream outfile{"computerplayer.txt"};
    if (initialize == true){
        for(auto v: Vertexes){
            bool judge = true;
            if(Vertexes.at(v->getNum())->getOwner() != -1){
               judge = false;
            } else {
                for(auto vnum: v->AdjacentVertex){
                    if(Vertexes.at(vnum)->getOwner() != -1){
                        judge = false;
                        break;
                    }    
                }
            }
            if(judge){
              outfile << v->getNum() << std::endl;
              display->CP_Basement(v->getNum());
              return;
            }
        }
    } else {
        outfile << "next" << std::endl;
        display->CP_Next();
    }
}
