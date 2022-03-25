#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "board.h"
#include "dice.h"
#include "InitialLevel.h"

class Controller {
    // pointer to the current boad
    std::shared_ptr<Board> board;
    std::shared_ptr<Level> lev;
    int seed;
    std::shared_ptr<Dice> dice;
    std::map<std::string, int> players;
    std::vector<int> numbers;
    std::default_random_engine rng;
    std::vector<int> computer_players;
    int p_size;

public:
    Controller(bool random = true, int seed = 246, int p = 4,
        int cp = 0,
        std::shared_ptr<std::istream> l = nullptr, 
        std::shared_ptr<std::istream> b = nullptr);

    // RollDice(type, num, computer) helps to roll the dice
    // type is true when the dice is fair and false when the dice is loaded. 
    // num is the loaded number when the type is set to false.
    // After rolling the dice, if the dice is 7, it calls board's Geese() to move the geese,
    // otherwise, it calls gainResource().
    void RollDice(bool type, int num = -1, bool computer = false);

    // BuildRoad(builder, edge) builds a road on the given edge
    void BuildRoad(int builder, int edge);

    // BuildRes(builder, vertex, first) builds a residence on the given vertex. It returns true 
    //  if the basement is built successfully; otherwise, false.
    bool BuildRes(int builder, int vertex, bool first);

    // Improve(builder, vertex) improves the residence on the given vertex
    void Improve(int builder, int vertex);

    // trade with the given builder. The current builder will give a resource (give)
    // and take a resource (take)
    void Trade(int builder, int give, int take);

    // Geese() calls the corresponding functions in board after getting instructions from the builder.
    void Geese();

    // go to the next Builder
    void next();

    // check if the Builder wins the game
    bool win(int builder);

    // restart the game
    void restart();

    // returns the current builder code
    int curTurn();

    // save the current game to the file named by the given string
    void save(std::string file = "backup.sv");

    // output the list of commands during the rolling dice section
    void help_dice();

    // output the list of commands during the player's section
    void help_play();

    // print the current board
    void printBoard();

    // print the current builder's status
    void printBuilderStatus();

    // print the current builder's residences
    void printResidences();

    // print(s) prints the string s
    void print(std::string s);

    // bank(v) tries to sale the residence and get some resource
    //   back to the current player
    void bank(int v);

    // market(give, take) let current player give four of the resources
    //   and take one of other type of resource
    void market(int give, int take);

    //  check_computer_player(player) checks whether the player is a computer 
    //   player
    bool check_computer_player(int player);

    // ComputerPlayerDecision(initialize) helps the computer to do the decision
    void ComputerPlayerDecision(bool initialize = false);


};

#endif
