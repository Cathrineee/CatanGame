#include "controller.h"
#include "Information.h"
#include "LoadedDice.h"
#include "FairDice.h"
#include "RandomLevel.h"
#include "PreviousLevel.h"
#include "CustomizedLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <random>
#include <vector>
#include <algorithm>
#include <set>

Controller::Controller(bool random, int seed, int p, int cp,
                       std::shared_ptr<std::istream> l,
                       std::shared_ptr<std::istream> b): seed{seed}, p_size{p} {
    players["Blue"] = 0;
    players["Red"] = 1;
    if (p >= 3) {
        players["Orange"] = 2;
    } 
    if (p == 4) {
        players["Yellow"] = 3;
    }

    int i = p - cp;
    while(i < p){
        computer_players.emplace_back(i);
        ++i;
    }

    rng.seed(seed);
    numbers = {1,2,3,4,5,6};
    if (random) lev = std::make_shared<RandomLevel>(p, seed);
    else if (l != nullptr) lev = std::make_shared<PreviousLevel>(p, l);
    else lev = std::make_shared<CustomizedLevel>(p, b);
    board = lev->getBoard();
}

void Controller::RollDice(bool type, int num, bool computer) {
    int roll;
    if (type) {
        std::shuffle(numbers.begin(), numbers.end(), rng);
        dice = std::make_shared<FairDice>(seed, numbers);
        roll = dice->rollDice();
        if(computer){
            while(roll == 7){
                std::shuffle(numbers.begin(), numbers.end(), rng);
                dice = std::make_shared<FairDice>(seed, numbers);
                roll = dice->rollDice();
            }
        }
    } else {
        dice = std::make_shared<LoadedDice>(num);
        roll = dice->rollDice();
    }
    if (roll == 7) Geese();
    else {
        if (type)
            print("The number you rolled is " + std::to_string(roll));
        board->gainResource(roll);
    }
}

void Controller::BuildRoad(int builder, int edge) { 
    board->BuildRoad(builder, edge); 
}
bool Controller::BuildRes(int builder, int vertex, bool first) { 
    return board->BuildBasement(builder, vertex, first); 
}
void Controller::Improve(int builder, int vertex) { 
    board->UpdateResidence(builder, vertex); 
}
void Controller::Trade(int builder, int give, int take) {
    board->Trade(builder, give, take);
}

void Controller::Geese() {
    std::cout << "The number you rolled is 7. You found a GEESE!" << std::endl;
    board->GeeseHalf(seed);
    std::set<std::string> builders;
    while(true) {
        std::cout << "Choose where to place the GEESE" << std::endl;
        std::string temp;
        std::cin >> temp;
        if (std::cin.fail()) std::cerr << "ERROR: invalid input." << std::endl;
        else {
            try {
                int v = std::stoi(temp);
                builders = board->UpdateGeese(v);
                bool invalid = false;
                for (auto s : builders) {
                    if (s == "?") {
                        std::cout << "Input an integer from 0 to 18." << std::endl;
                        std::cout << "> ";
                        invalid = true;
                    }
                }
                if (!invalid) break;
            } catch (std::invalid_argument &x) {
                std::cerr << "ERROR: " << temp << " isn't a valid integer." << std::endl;
            }
        }
    }
    if (builders.empty()) return;
    while(true) {
        std::cout << "Choose a builder to steal from:" << std::endl;
        std::string b;
        std::cin >> b;
        if (std::cin.fail()) std::cerr << "ERROR: invalid input" << std::endl;
        else if (players.find(b) == players.end()) std::cerr << "ERROR: not a valid builder" << std::endl;
        else {
            board->StealBuilder(players[b], seed);
            break;
        }
    }
}

int Controller::curTurn() { return board->GetCurrentTurn(); }
void Controller::next() { board->next(p_size); }
bool Controller::win(int builder) { return board->win(builder); }
void Controller::restart() { 
    board = lev->restartBoard();
}
void Controller::save(std::string file) { board->SavedBoard(file); }

void print(std::string s) { std::cout << s << std::endl; }

void Controller::help_dice() {
    print("Valid commands:");
    print("~ load : changes current builder's dice type to 'loaded'");
    print("~ fair : changes current builder's dice type to 'fair'");
    print("~ roll : rolls the dice and distributes resources.");
    print("~ status : prints the current status of all builders in order from builder 0 to 3.");
    print("~ help : prints out the list of commands.");
}
void Controller::help_play() {
    print("Valid commands:");
    print("~ board : prints the current board.");
    print("~ status : prints the current status of all builders in order from builder 0 to 3.");
    print("~ residences : prints the residences the current builder has currently completed.");
    print("~ build-road <road#> : attempts to builds the road at <road#>.");
    print("~ build-res <housing#> : attempts to builds a basement at <housing#>.");
    print("~ improve <housing#> : attempts to improve the residence at <housing#>.");
    print("~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>.");
    print("~ bank : attempts to apply for a mortgage using an existing residence. Further instructions will be given when the command is chosen.");
    print("~ market <give> <take> : attempts to trade with the market, giving four resources of type <give> and receiving one resource of type <take>.");
    print("~ next : passes control onto the next builder in the game.");
    print("~ save <file> : saves the current game state to <file>.");
    print("~ help : prints out the list of commands.");
}

void Controller::printBoard() { board->printBoard(); }
void Controller::printBuilderStatus() { board->printBuilder(); }
void Controller::printResidences() { board->printResidences(); }

void Controller::print(std::string s) { std::cout << s << std::endl; }
void Controller::bank(int v) { 
    board->SaleHouse(v); }
void Controller::market(int give, int take) { board->ExchangeResource(give, take); }

bool Controller::check_computer_player(int player){
    if(std::count(computer_players.begin(), computer_players.end(), player)){
        return true;
    } else {
        return false;
    }
}

void Controller::ComputerPlayerDecision(bool initialize){
    board->ComputerPlayerDecision(initialize);
}
