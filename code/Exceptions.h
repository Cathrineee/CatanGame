#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <iostream>

struct alreadySpecified{
    std::string already;
    std::string tryTo;

    alreadySpecified(std::string already, std::string tryTo = "");
};

struct unableOpen{
    std::string file;
    unableOpen(std::string file);
};

struct invalidArg{ 
    std::string arg;
    invalidArg(std::string arg);
};

struct InvalidCommand {
    std::string msg;
    InvalidCommand(std::string msg = "");
};

struct EndOfGame{
    std::string winner;
    EndOfGame(std::string winner);
};


void InvalidInteger(std::string q = "");
void invalidUpdate(int result);

#endif
