#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ostream>
#include <algorithm>
#include "controller.h"
#include "Exceptions.h"

int main (int argc, char* argv[]) {
    std::string file = "layout.txt";
    std::shared_ptr<std::istream> l = nullptr;
    std::shared_ptr<std::istream> b = nullptr;
    bool seed = false;
    bool load = false;
    bool board = false;
    bool random = false;
    bool players_size = false;
    bool computer = false;
    int s = 246;
    int p = 4;
    int cp = 0;
    try{
        for (int i = 1; i < argc; ++i) {
            std::string arg{argv[i]};
            if (arg.compare("-seed") == 0) {
                if (seed) throw alreadySpecified(arg);
                seed = true;
                std::string num{argv[++i]};
                s = std::stoi(num);
            } else if (arg.compare("-load") == 0) {
                if (load) throw alreadySpecified(arg);
                if (board) throw alreadySpecified("-board", arg);
                if (random) throw alreadySpecified("-random", arg);
                load = true;
                file = argv[++i];
            } else if (arg.compare("-board") == 0) {
                if (board) throw alreadySpecified(arg);
                if (load) throw alreadySpecified("-load", arg);
                if (random) throw alreadySpecified("-random", arg);
                board = true;
                file = argv[++i];
            } else if (arg.compare("-random-board") == 0) {
                if (random) throw alreadySpecified(arg);
                if (load) throw alreadySpecified("-load", arg);
                if (board) throw alreadySpecified("-board", arg);
                random = true;
            } else if (arg.compare("-players") == 0) {
                if (players_size) throw alreadySpecified(arg);
                p = std::stoi(argv[++i]);
                if (p < 2 || p > 4) {
                    std::cerr << "ERROR: invalid player size." << std::endl;
                    return 0;
                }
                players_size = true;
            } else if (arg.compare("-computer_player") == 0) {
                if (computer) throw alreadySpecified(arg);
                cp = std::stoi(argv[++i]);
                computer = true;
            } else {
                throw std::invalid_argument("ERROR: unregonized argument " + arg);
            }
        }
        if(computer){if (cp < 1 || cp > p - 1) {
                    std::cerr << "ERROR: invlaid computer player size." << std::endl;
            return 0;
        }}
        if (!board && !load) random = true;
        if (!random) {
            std::shared_ptr<std::istream> temp(new std::ifstream(file));
            if (temp == nullptr || temp->fail())
                throw unableOpen(file);
            if (load)
                l = temp;
            else if (board)
                b = temp;
        }
    } catch (alreadySpecified x) {
        if (x.tryTo == "") {
            std::cerr << "ERROR: already specified " + x.already + " once before" << std::endl;
        } else {
            std::cerr << "ERROR: already specified " + x.already + ", can't also specify " + x.tryTo << std::endl;
        }
        return 0;
    } catch (unableOpen x) {
        if (x.file == "layout.txt") {
            std::cerr << "ERROR: Unable to open file " + x.file + " for default board layout." << std::endl;
        } else {
            std::cerr << "ERROR: Unable to open file " + x.file + " for board layout." << std::endl;
        }
        return 0;
    } catch (std::invalid_argument &x) {
        std::cerr << "ERROR:  isn't a valid integer." << std::endl;
        return 0;
    }
    Controller c;
    try {
        c = Controller(random, s, p, cp, l, b);
    } catch (std::invalid_argument &x) {
        std::cerr << "ERROR: " << file << " is in invalid format." << std::endl;
        return 0;
    }

    std::cin.exceptions(std::ios::eofbit);
    std::vector<std::string> PLAYERS = {"Blue", "Red"};
    if (p >= 3) {
        PLAYERS.emplace_back("Orange");
    }
    if (p == 4) {
        PLAYERS.emplace_back("Yellow");
    }
    const std::vector<std::string> RESOURCES = {"BRICK", "ENERGY", "GLASS", "HEAT", "WIFI"};
    const std::vector<std::string> RESIDENCE = {"Basement", "House", "Tower"};
    bool again = true;
    std::string in;

    while(again) {
        if (c.curTurn() < 0) {
            try {
        // beginning of Game
        c.printBoard();
        for (size_t i = 0; i < PLAYERS.size(); ++i) {
            std::cout << "Builder " << PLAYERS[i] << ", where do you want to build a basement?" << std::endl;
            while(true) {
                std::cout << "> ";
                std::string temp;
                std::ifstream infile{"computerplayer.txt"};
                int vertex;
                if (c.check_computer_player(i)) {
                    c.ComputerPlayerDecision(true);
                    infile >> temp;
                } else std::cin >> temp;
                if ((std::cin.fail()) && (!c.check_computer_player(i))) {
                    std::cerr << "ERROR: invalid input." << std::endl;
                } else {
                    try {
                        vertex = std::stoi(temp);
                        if (c.BuildRes(i, vertex, true))
                            break;
                    } catch (std::invalid_argument &x) {
                        InvalidInteger(temp);
                    }
                }
            }
        }
        for (size_t i = PLAYERS.size(); i > 0; --i) {
            std::cout << "Builder " << PLAYERS[i-1] << ", where do you want to build a basement?" << std::endl;
            while (true) {
                std::cout << "> ";
                std::string temp;
                std::ifstream infile{"computerplayer.txt"};
                int vertex;
                if (c.check_computer_player(i-1)) {
                    c.ComputerPlayerDecision(true);
                    infile >> temp;
                } else std::cin >> temp;
                if ((std::cin.fail()) && (!c.check_computer_player(i))) {
                    std::cerr << "ERROR: invalid input." << std::endl;
                } else {
                    try{
                        vertex = std::stoi(temp);
                        if (c.BuildRes(i-1, vertex, true)) break;
                    } catch (std::invalid_argument &x) {
                        InvalidInteger(temp);
                    }
                }
            }
        }
        c.next();
    } catch (std::ios::failure x) {
        std::cerr << "End of file reached." << std::endl;
        std::cerr << std::endl;
        return 0;
    } }

    try {
        // Game start
        c.printBoard(); // print updated board
        bool first = true;
        int start_player = c.curTurn();
        while (true) {
            if (!first) start_player = 0;
            for (size_t i = start_player; i < PLAYERS.size(); ++i) {
                // if rolled dice is fair, dice_type is true; otherwise, false.
                bool dice_type = false;
                c.print("Builder " + PLAYERS[i] + "'s turn.");
                
                // Beginning of Turn

                bool loop_1 = true;
                while(loop_1) {
                    try {
                        std::cout << "> ";
                        if (c.check_computer_player(i)){
                            c.RollDice(true, -1, true);
                            break;
                        } else std::cin >> in;
                        if (in.compare("load") == 0) {
                            dice_type = false;
                            c.print("Builder " + PLAYERS[i] + " now has loaded Dice.");
                        }
                        else if (in.compare("fair") == 0) {
                            dice_type = true;
                            c.print("Builder " + PLAYERS[i] + " now has fair Dice.");
                        }
                        else if (in.compare("roll") == 0) {
                            if (dice_type) {
                                c.RollDice(dice_type);
                                loop_1 = false;
                            } else {
                                bool loop_2 = true;
                                while (loop_2) {
                                c.print("Input a roll between 2 and 12:");
                                std::cout << "> ";
                                std::string temp;
                                int num;
                                std::cin >> temp;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                } else {
                                    try {
                                        num = std::stoi(temp);
                                        if (num < 2 || num > 12) {
                                            std::cerr << "Invalid roll " << num << std::endl;
                                        } else {
                                            c.RollDice(dice_type, num);
                                            loop_2 = false;
                                            loop_1 = false;
                                        }
                                    } catch (std::invalid_argument &x) {
                                        InvalidInteger(temp);
                                        std::cout << "Input a integer from 2 to 12." << std::endl;
                                        std::cout << "> ";
                                    }
                                }
                            }
                            }
                        } else if (in.compare("status") == 0) c.printBuilderStatus();
                        else if (in.compare("help") == 0) c.help_dice();
                        else throw InvalidCommand();
                    } catch (InvalidCommand x) {
                        std::cerr << "Invalid command." << std::endl;
                        std::cerr << "Please enter 'help' for a list of valid commands." << std::endl;
                    }
                }

                // During the Turn

                loop_1 = true;
                while(loop_1) {
                    try {
                        c.print("Enter a command:");
                        std::cout << "> ";
                        std::ifstream infile{"computerplayer.txt"};
                        if (c.check_computer_player(i)) {
                            c.ComputerPlayerDecision(false);
                            infile >> in;
                        } else std::cin >> in;
                        if (in.compare("board") == 0) c.printBoard();
                        else if (in.compare("status") == 0) c.printBuilderStatus();
                        else if (in.compare("residences") == 0) c.printResidences();
                        else if (in.compare("build-road") == 0) {
                            std::string temp;
                            int edge;
                            while(true) {
                                std::cin >> temp;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                } else {
                                    try {
                                        edge = std::stoi(temp);
                                        c.BuildRoad(i, edge);
                                        break;
                                    } catch (std::invalid_argument &x) {
                                        InvalidInteger(temp);
                                        std::cout << "Input a integer from 0 to 71." << std::endl;
                                        std::cout << "> ";
                                    }
                                }
                            }
                        } else if (in.compare("build-res") == 0) {
                            int vertex;
                            while (true) {
                                std::string temp;
                                std::cin >> temp;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                } else {
                                    try {
                                        vertex = std::stoi(temp);
                                        c.BuildRes(i, vertex, false);
                                        if (c.win(i))
                                            throw EndOfGame(PLAYERS[i]);
                                        else
                                            break;
                                    } catch (std::invalid_argument &x) {
                                        InvalidInteger(temp);
                                        std::cout << "Input a integer from 0 to 53." << std::endl;
                                        std::cout << "> ";
                                    }   
                                }
                            }
                        } else if (in.compare("improve") == 0) {
                            int vertex;
                            while(true) {
                                std::string temp;
                                std::cin >> temp;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                } else {
                                    try {
                                        vertex = std::stoi(temp);
                                        c.Improve(i, vertex);
                                        if (c.win(i))
                                            throw EndOfGame(PLAYERS[i]);
                                        else break;
                                    } catch (std::invalid_argument &x) {
                                        InvalidInteger(temp);
                                        std::cout << "Input a integer from 0 to 71." << std::endl;
                                        std::cout << "> ";
                                    }   
                                }
                            }
                        } else if (in.compare("trade") == 0) {
                            std::string builder;
                            std::string give;
                            std::string take;
                            while(true) {
                                std::cin >> builder >> give >> take;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                    std::cout << "> ";
                                } else {
                                    auto player = std::find(PLAYERS.begin(), PLAYERS.end(), builder);
                                    auto give_pos = std::find(RESOURCES.begin(), RESOURCES.end(), give);
                                    auto take_pos = std::find(RESOURCES.begin(), RESOURCES.end(), take);
                                    if (player == PLAYERS.end() ||
                                        give_pos == RESOURCES.end() ||
                                        take_pos == RESOURCES.end()) throw InvalidCommand();

                                    c.print(PLAYERS[i] + " offers " + *player + " one " + *give_pos + " for one " + *take_pos + ".");
                                    c.print("Does " + *player + " accept this offer?");
                                    std::cout << "> ";
 
                                    while(true) {
                                        if(c.check_computer_player(player - PLAYERS.begin())){
                                          in = "no";
                                          std::cout << "no" << std::endl;   
                                        } else {
                                         std::cin >> in;
                                        }
                                        if (in.compare("yes") == 0) {
                                            c.Trade(player - PLAYERS.begin(), give_pos - RESOURCES.begin(), take_pos - RESOURCES.begin());
                                            break;
                                        }
                                        else if (in.compare("no") == 0) break;
                                        else {
                                            std::cerr << "Please respond by 'yes' or 'no'." << std::endl;
                                            std::cout << "> ";
                                        }
                                    }
                                    break;
                                }
                            }
                        } else if (in.compare("next") == 0) loop_1 = false;
                        else if (in.compare("save") == 0) {
                            std::string file;
                            std::cin >> file;
                            if (std::cin.fail()) {
                                std::cerr << "ERROR: invalid input." << std::endl;
                            } else {
                                c.save(file);
                            }
                        } else if (in.compare("help") == 0) {
                            c.help_play();
                        } else if (in.compare("bank") == 0) {
                            std::cout << "Here is the rules for applying a mortgage." << std::endl;
                            std::cout << "          Original price                                What you will get" << std::endl;
                            std::cout << "Basement: 1 BRICK, 1 ENERGY, 1 GLASS, 0 HEAT, 1 WIFI => 1 BRICK, 1 ENERGY, 0 GLASS, 0 HEAT, 0 WIFI" << std::endl;
                            std::cout << "House   : 0 BRICK, 0 ENERGY, 2 GLASS, 3 HEAT, 0 WIFI => 1 BRICK, 1 ENERGY, 1 GLASS, 1 HEAT, 0 WIFI" << std::endl;
                            std::cout << "Tower   : 3 BRICK, 2 ENERGY, 2 GLASS, 2 HEAT, 1 WIFI => 2 BRICK, 2 ENERGY, 2 GLASS, 2 HEAT, 1 WIFI" << std::endl;
                            std::cout << "Enter the vertex if you want to continue, or else 'quit'." << std::endl;
                            std::cout << "> ";

                            std::string temp;
                            while(true) {
                                std::cin >> temp;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input" << std::endl;
                                    std::cout << "> ";
                                } else if (temp.compare("quit") == 0) {
                                    break;
                                } else {
                                    int v;
                                    try {
                                        v = std::stoi(temp);
                                        c.bank(v);
                                        break;
                                    } catch (std::invalid_argument &x) {
                                        InvalidInteger();
                                        std::cout << "Please input an integer from 0 to 53 or 'quit'." << std::endl;
                                        std::cout << "> ";
                                    }
                                }
                            }
                        } else if (in.compare("market") == 0) {
                            std::string t1, t2;
                            while(true) {
                                std::cin >> t1 >> t2;
                                if (std::cin.fail()) {
                                    std::cerr << "ERROR: invalid input." << std::endl;
                                } else {
                                    auto give = std::find(RESOURCES.begin(), RESOURCES.end(), t1);
                                    auto take = std::find(RESOURCES.begin(), RESOURCES.end(), t2);
                                    if (give == RESOURCES.end()) {
                                        std::cerr << "ERROR: " << t1 << " is not a valid resource." << std::endl;
                                        std::cout << "> ";
                                    } else if (take == RESOURCES.end()) {
                                        std::cerr << "ERROR: " << t2 << " is not a valid resource." << std::endl;
                                        std::cout << "> ";
                                    } else {
                                        c.market(give-RESOURCES.begin(), take-RESOURCES.begin());
                                        break;
                                    }
                                }
                            }
                        }
                        else throw InvalidCommand();
                    } catch (InvalidCommand x) {
                        std::cerr << "Invalid command." << std::endl;
                        std::cerr << "Please enter 'help' for a list of valid commands." << std::endl;
                    }
                }
                c.next();
            }
            first = false;
        }
    } catch (EndOfGame x) {
        c.print("Congratulations to " + x.winner + "! You have won the game!");
        for (size_t i = 0; i < PLAYERS.size(); ++i) {
            c.print("Builder " + PLAYERS[i] + ", would you like to play again?");
            std::string res;
            while (true) {
                std::cin >> res;
                if (std::cin.fail()) {
                    std::cerr << "ERROR: invalid input." << std::endl;
                    std::cout << "> ";
                } else if (res.compare("yes") == 0) break;
                else if (res.compare("no") == 0) {
                    again = false;
                    break;
                } else {
                    std::cerr << "Invalid command. Please enter 'yes' or 'no'." << std::endl;
                    std::cout << "> ";
                }
            }
            if (!again) break;
        }
        if (again) { c.restart(); }
    } catch (std::ios::failure x) {
        again = false;
        std::cerr << "End of file reached." << std::endl;
        std::cerr << std::endl;
        c.save();
        c.print("Saving to backup.sv...");
    }
    }
}

