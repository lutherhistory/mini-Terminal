#include "../include/System.hpp"
#include <iostream>

void System::signUpUser(){
    std::string name, password;

    id++;

    std::cout << color("> Username: ", "1;33");
    std::cin >> name;
    std::cout << color("> Password: ", "1;33");
    std::cin >> password;

    data.save({"machine", "using_id"}, id);

    data.append({"users"}, {
        {"current_dir", "/home/" + name},
        {"history_file", name + ".history"},
        {"home_dir", "/home/" + name},
        {"id", id},
        {"is_admin", false},
        {"name", name},
        {"password_hash", password},
        {"theme", {}}
    });
}

void System::verifyLogin(){
    std::string name, password;

    login:
    std::cout << color("Login as: ", "1;34");
    std::cin >> name;

    for (int count = 0; count < data.value({"machine", "user_count"}); count++){
        if (name == data.value({"users", std::to_string(count), "name"})){
            std::cout << color("Password for " + name +": ", "1;31");
            std::cin >> password;
        }else {
            goto login;
        }
    }
}

void System::deleteUser(){

}

std::string System::color(const std::string& text, const std::string& code){
    return "\033[" + code + "m" + text + "\033[0m";
}

System::System(): data("../settings/system.json"){
    raw_data = data.exportString();
    id = data.value({"machine", "using_id"});

    if (id == 0){
        signUpUser();

    }else {
        verifyLogin();
    }
}
