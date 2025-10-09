#include "include/System.hpp"
#include "include/Terminal.hpp"

#include <iostream>
// #include <fstream>

using namespace std;

int main() {
    Terminal terminal;
    System program;
    std::string command;

    do {
        program.renderPath();
        cin >> command;

        terminal.set(command);

        if (command != "exit")
            terminal.response();
        else {
            cout << "\033[0m";
            return 0;
        }

    } while (true);

    return 1;
}
