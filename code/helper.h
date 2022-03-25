#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <map>
#include <vector>

// adjacentEdge() is a helper function to find the adjacent edge
//   of a vertex
std::map<int, std::vector<int> > adjacentEdge();

// adjacentVertex() is a helper function to find the adjacent
//   vertex of a vertex
std::map<int, std::vector<int> > adjacentVertex();

// findEdgeVerticies() is a functionthat finds the vertex of
//   edges
std::map<int, std::vector<int>> findEdgeVerticies();

// edgeToEdge() is a function to find the adjacent edges of
//   an edge
std::map<int, std::vector<int>> edgeToEdge();

// createBuilderInfoMap() creates a builder information map
//   from builder ID to builder name
std::map<int, std::string> createBuilderInfoMap();

// TileToVertex() helps to find all the vertex of each tile
std::map<int, std::vector<int>> TileToVertex();

#endif
