#pragma once

#include <string>

class Terminal {
    private:
        std::string command;

    private:
        bool checkIsValid();

    public:
        void set(std::string command);

        void response();

        // Terminal(User);
};
