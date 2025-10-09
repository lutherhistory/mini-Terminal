#pragma once

#include "System.hpp"
#include <string>
#include <fstream>

class Terminal {
    private:
        std::string command;
        std::string file_name = "../back-end/history.txt";
        std::fstream file;

        System os;

    private:
        void help();
        void history();

    public:
        void response();

        void set(std::string);
};
