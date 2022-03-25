#include "Exceptions.h"
#include <string>
#include <iostream>

alreadySpecified::alreadySpecified(std::string already, std::string tryTo) : already{already}, tryTo{tryTo} {}

unableOpen::unableOpen(std::string file) : file{file} {}

invalidArg::invalidArg(std::string arg) : arg{arg} {}

InvalidCommand::InvalidCommand(std::string msg) : msg{msg} {}

EndOfGame::EndOfGame(std::string winner) : winner{winner} {}

void InvalidInteger(std::string q) {
    std::cerr << "ERROR: " + q + " isn't a valid integer." << std::endl;
}

void invalidUpdate(int result) {
    std::string msg;
    if (result == 1) {
        msg = "The cost to improve a Basement to a House is two GLASS and three HEAT resource.";
    }
    else if (result == 2)  {
        msg = "The cost to improve a House to a Tower is three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT.";
    }
    else if (result == 3)  {
        msg = "You cannot improve a Tower.";
    }
    else  {
        msg = "Invalid Residence.";
    }
    std::cerr << msg << std::endl;
}
