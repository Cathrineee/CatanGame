#include "helper.h"

std::map<int, std::vector<int> > adjacentEdge() {
    std::map<int, std::vector<int>> ret;
    std::vector<int> edges{-1, 0, 1};
    for (int i = 0; i < 54; ++i) {
        if (i == 0) edges = {-1, 0, 1};
        else if (i == 1) edges = {-1,0,2};
        else if (i == 2) edges = {-1,3,5};
        else if (i == 3) edges = {1,3,6};
        else if (i == 4) edges = {2,4,7};
        else if (i == 5) edges = {-1,4,8};
        else if (i == 6) edges = {-1,9,12};
        else if (i == 7) edges = {5,9,13};
        else if (i == 8) edges = {6,10,14};
        else if (i == 11) edges = {-1,11,17};
        else if (i == 12) edges = {12,-1,20};
        else if (i == 13) edges = {13,18,21};
        else if (i == 14) edges = {14,18,22};
        else if (i == 17) edges = {17,-1,25};
        else if (i == 18) edges = {20,26,29};
        else if (i == 19) edges = {21, 26, 30};
        else if (i == 20) edges = {22, 27, 31};
        else if (i == 42) edges = {54,60,-1};
        else if (i == 43) edges = {55, 60, 63};
        else if (i == 44) edges = {56, 61, 64};
        else if (i == 47) edges = {59,62,-1};
        else if (i == 48) edges = {63,67,-1};
        else if (i == 49) edges = {64,67,69};
        else if (i == 50) edges = {65,68,70};
        else if (i == 51) edges = {66,68,-1};
        else if (i == 52) edges = {69,71,-1};
        else if (i == 53) edges = {70,71,-1};
        else if (i % 12 == 0 || i % 12 == 5) {
            edges[0] = ret[i-12][0] + 17;
            edges[1] = ret[i - 12][1];
            edges[2] = ret[i-12][2] + 17;
        } else if (i % 12 == 1 || i % 12 == 2 || i % 12 == 6 || i % 12 == 7 || i % 12 == 8) {
            edges[0] = ret[i-12][0] + 17;
            edges[1] = ret[i-12][1] + 17;
            edges[2] = ret[i-12][2] + 17;
        } else {
            std::vector<int> prev = ret[i-2];
            if (prev[0] > 0) edges[0] = prev[0] + 2;
            if (prev[1] > 0) edges[1] = prev[1] + 1;
            if (prev[2] > 0) edges[2] = prev[2] + 2;
        }
        ret.emplace(i, edges);
    }
    return ret;
}

std::map<int, std::vector<int> > adjacentVertex() {
    std::map<int, std::vector<int>> ret;
    std::vector<int> edges;
    for(int i = 0; i < 54; ++i){
        if((i % 6 == 0) && (i>=6) && (i<=42)){
            if(i == 6) edges = {7, 12};     
            else if(i == 42) edges = {36, 43};
            else if(i % 12 == 0) edges = {i+6, i-6};
            else edges = {i+1, i-6, i+6};
        } else if((i % 6 == 5) && (i>=11) && (i<=47)){
            if(i == 11) edges = {10,17};     
            else if(i == 47) edges = {41,46};
            else if(i % 12 == 5) edges = {i-6,i+6};
            else edges = {i-1, i-6, i+6};
        } else if((i>=13)&&(i<=40)) {
            if ((i % 12 == 1) || (i % 12 == 8) ||
                (i % 12 == 3) || (i % 12 == 10)) {
                edges = {i+1,i-6, i+6};
            } else {
                edges = {i-1,i-6, i+6};
            }
        } else if((i>=7)&&(i<=10)) {
            if((i % 6 == 1)||(i % 6 == 3)){
                edges = {i-1,i-5, i+6};
            } else {
                edges = {i+1,i-5, i+6};
            }
        }
          else if((i>=43)&&(i<=46)) {
            if((i % 6 == 1)||(i % 6 == 3)){
                edges = {i-1,i-6, i+5};
            } else {
                edges = {i+1,i-6, i+5};
            }  
          }
          else if(i==2) edges = {3,7}; 
          else if(i==5) edges = {4,10}; 
          else if(i==48) edges = {43,49}; 
          else if(i==51) edges = {46,50};
          else if(i==5) edges = {4,10};
          else if(i==3) edges = {0,2,8};
          else if(i==4) edges = {1,5,9};
          else if(i==49) edges = {44,48,52};
          else if(i==50) edges = {45,51,53}; 
          else if(i==0) edges = {1,3};
          else if(i==1) edges = {0,4};
          else if(i==52) edges = {49,53};
          else if(i==53) edges = {50,52};
        ret.emplace(i, edges);
    }
    return ret;
}

std::map<int, std::vector<int>> findEdgeVerticies()
{
    std::vector<int> v;
    std::map<int, std::vector<int>> myMap;
    for (int i = 0; i < 72; ++i)
    {
        if (i == 0)
            v = {0, 1};
        else if (i == 1)
            v = {0, 3};
        else if (i == 2)
            v = {1, 4};
        else if (i == 3)
            v = {2, 3};
        else if (i == 4)
            v = {4, 5};
        else if (i == 5)
            v = {2, 7};
        else if (i <= 8)
        {
            v[0] = myMap[i - 1][0] + 1;
            v[1] = myMap[i - 1][1] + 1;
        }
        else if (i <= 62)
        {
            if (i % 17 == 1)
            {
                v[0] = 12 * (i / 17) + 1;
                v[1] = 12 * (i / 17) + 2;
            }
            else if (i % 17 == 2)
            {
                v[0] = 12 * (i / 17) + 3;
                v[1] = 12 * (i / 17) + 4;
            }
            else if (i % 17 >= 3 && i % 17 <= 8)
            {
                v[0] = 12 * (i / 17) + i % 17 - 3;
                v[1] = 12 * (i / 17) + i % 17 + 3;
            }
            else if (i % 17 == 9)
            {
                v[0] = 12 * (i / 17) + 6;
                v[1] = 12 * (i / 17) + 7;
            }
            else if (i % 17 == 10)
            {
                v[0] = 12 * (i / 17) + 8;
                v[1] = 12 * (i / 17) + 9;
            }
            else if (i % 17 == 11)
            {
                v[0] = 12 * (i / 17) + 10;
                v[1] = 12 * (i / 17) + 11;
            }
            else if (i % 17 == 0)
            {
                v[0] = 12 * (i / 17) - 1;
                v[1] = 12 * (i / 17) + 5;
            }
            else
            {
                v[0] = 12 * (i / 17) + i % 17 - 6;
                v[1] = 12 * (i / 17) + i % 17;
            }
        }
        else if (i == 63)
            v = {43, 48};
        else if (i <= 66)
        {
            v[0] = myMap[i - 1][0] + 1;
            v[1] = myMap[i - 1][1] + 1;
        }
        else if (i == 67)
            v = {48, 49};
        else if (i == 68)
            v = {50, 51};
        else if (i == 69)
            v = {49, 52};
        else if (i == 70)
            v = {50, 53};
        else
            v = {52, 53};
        myMap.emplace(i, v);
    }
    return myMap;
}

std::map<int, std::string> createBuilderInfoMap(){
    std::map<int, std::string> buildinfo;
    buildinfo[0] = "Blue";
    buildinfo[1] = "Red";
    buildinfo[2] = "Orange";
    buildinfo[3] = "Yellow";
    return buildinfo;
}

std::map<int, std::vector<int>> edgeToEdge()
{
    std::map<int, std::vector<int>> myMap;
    std::map<int, std::vector<int>> edgeVerticies = findEdgeVerticies();
    std::map<int, std::vector<int>> adjacentEdges = adjacentEdge();
    for (int i = 0; i <= 71; ++i)
    {
        std::vector<int> res;
        std::vector<int> v = edgeVerticies[i];
        for (size_t j = 0; j < v.size(); ++j)
        {
            std::vector<int> e = adjacentEdges[v[j]];
            for (auto x : e)
            {
                if (x != i && x != -1)
                    res.emplace_back(x);
            }
        }
        myMap.emplace(i, res);
    }
    return myMap;
}

std::map<int, std::vector<int>> TileToVertex(){
    std::map<int, std::vector<int>> tileToVertex;
    std::vector<int> t0 = {0,1,3,4,8,9};
    tileToVertex[0] = t0;
    std::vector<int> t1 = {2,3,7,8,13,14};
    tileToVertex[1] = t1;
    std::vector<int> t2 = {4,5,9,10,15,16};
    tileToVertex[2] = t2;
    std::vector<int> t3 = {6,7,12,13,18,19};
    tileToVertex[3] = t3;
    std::vector<int> t4 = {8,9,14,15,20,21};
    tileToVertex[4] = t4;
    std::vector<int> t5 = {10,11,16,17,22,23};
    tileToVertex[5] = t5;
    std::vector<int> t6 = {13,14,19,20,25,26};
    tileToVertex[6] = t6;
    std::vector<int> t7 = {15,16,21,22,27,28};
    tileToVertex[7] = t7;
    std::vector<int> t8 = {18,19,24,25,30,31};
    tileToVertex[8] = t8;
    std::vector<int> t9 = {20,21,26,27,32,33};
    tileToVertex[9] = t9;
    std::vector<int> t10 = {22,23,28,29,34,35};
    tileToVertex[10] = t10;
    std::vector<int> t11 = {25,26,31,32,37,38};
    tileToVertex[11] = t11;
    std::vector<int> t12 = {27,28,33,34,39,40};
    tileToVertex[12] = t12;
    std::vector<int> t13 = {30,31,36,37,42,43};
    tileToVertex[13] = t13;
    std::vector<int> t14 = {32,33,38,39,44,45};
    tileToVertex[14] = t14;
    std::vector<int> t15 = {34,35,40,41,46,47};
    tileToVertex[15] = t15;
    std::vector<int> t16 = {37,38,43,44,48,49};
    tileToVertex[16] = t16;
    std::vector<int> t17 = {39,40,45,46,50,51};
    tileToVertex[17] = t17;
    std::vector<int> t18 = {44,45,49,50,52,53};
    tileToVertex[18] = t18;
    return tileToVertex;
}
