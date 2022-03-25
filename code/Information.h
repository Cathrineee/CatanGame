#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>
#include <vector>
#include "BuilderData.h"

class BuilderData;

class Information {
   public:
   // the number of the current player
   int CurTurn;
   // data for the builder
   BuilderData builder0Data;
   BuilderData builder1Data;
   BuilderData builder2Data;
   BuilderData builder3Data;
   // board data
   std::vector<int> board;
   // the vertex current geese is on. -1 if no geese exists.
   int geese;
};

#endif
