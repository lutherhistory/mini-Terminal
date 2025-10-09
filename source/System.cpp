#include "../include/System.hpp"

#include <iostream>
#include <string>

void System::renderPath(){
    std::cout << "\033[38;2;0;255;180m" << user << "\033[0m"
              << "\033[37m@"
              << "\033[38;2;255;200;0mmini-Terminal\033[0m"
              << "\033[37m:"
              << "\033[38;2;0;200;255m " << "~" + path << "\033[0m"
              << "\033[97m$ ";
}

void System::set(){
    file.open(file_name, std::ios::in);
    std::string line, str;

    if (!file.is_open()){
        std::cerr << "Failed to open the source: " << file_name << std::endl;
        return;
    }

    while (getline(file, line)){
        str += line;
    }

    file.close();

    data = data.parse(str);
    user = data["user"];
    password = data["password"];
    path = data["path"];
}

void System::update(){
    file.open(file_name, std::ios::out);

    if (!file.is_open()){
        std::cerr << "Failed to open the source: " << file_name << std::endl;
        return;
    }

    data = {
        {"user", user},
        {"password", password},
        {"path", path}
    };

    file << data.dump(4);

    file.close();
}

void System::get(std::string text){
    if (text == "path"){
        std::cout << "home/" << user;

        if (!path.empty())
            std::cout << '/' << path;

        std::cout << std::endl;
    }else if (text == "user"){
        std::cout << user << std::endl;
    }
}

System::System(){
    set();

    if (user.empty() && password.empty()){
        std::cout << "Enter your user name: ";
        std::cin >> user;

        std::string file_n = "mkdir ../back-end/home/" + user;

        system(file_n.c_str());

        std::cout << "Enter your password: ";
        std::cin >> password;
    }

    update();
}
