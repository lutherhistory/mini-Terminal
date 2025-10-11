#include "../include/Terminal.hpp"

#include <iostream>

bool Terminal::checkIsValid() {
    return true;
}

void Terminal::set(std::string command) {
    this->command = command;
}

void Terminal::response() {
    if (command == "help") {
        system("python3 -m webbrowser ../help.html");
        std::cout << "help: Help is being displayed in your browser" << std::endl;
    }else if (command == "clear"){
        system("clear");
    }else if (command == "whoami"){

    }else {
        std::cout << "Unknown command: " << command << "\n";
    }
}

// Terminal::Terminal(User user) {
//     this->user = user;
// }
