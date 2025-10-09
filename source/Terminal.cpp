#include "../include/Terminal.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

// Rendering or Response
void Terminal::response(){
    if (command == "help"){
        help();
    }else if (command == "clear"){
        system("clear");
    }else if (command == "history"){
        history();
    }else if (command == "pwd"){
        os.get("path");
    }else if (command == "whoami"){
        os.get("user");
    }else if (command == "date"){
        system("date");
    }
    else {
        std::cout << "miniShell: Unknown command: " << command << std::endl;
    }
}

void Terminal::set(std::string cmd){
    if (cmd != "history"){
        file.open(file_name, std::ios::app);

        if (file.is_open())
            file << cmd << std::endl;

        file.close();
    }
    command = cmd;
}

// Commands
void Terminal::help(){
    std::cout << "MiniTerminal - Supported Commands\n\n";

    std::cout << "Internal Commands:\n";
    std::cout << "  help       - Show this help message\n";
    std::cout << "  exit       - Exit the terminal\n";
    std::cout << "  clear      - Clear the terminal screen\n";
    std::cout << "  pwd        - Show current working directory\n";
    std::cout << "  cd <dir>   - Change current directory\n";
    std::cout << "  history    - Show previously entered commands\n\n";

    std::cout << "External Commands:\n";
    std::cout << "  ls         - List files and directories\n";
    std::cout << "  cat <file> - Display file contents\n";
    std::cout << "  echo       - Print text to the terminal\n";
    std::cout << "  mkdir <dir>- Create a new directory\n";
    std::cout << "  rmdir <dir>- Remove an empty directory\n";
    std::cout << "  whoami     - Show current username\n";
    std::cout << "  date       - Show system date and time\n\n";
}

void Terminal::history(){
    file.open(file_name, std::ios::in);
    std::string str;

    if (!file.is_open())
        return;

    while (std::getline(file, str)){
        std::cout << str << std::endl;
    }

    file.close();
}
