#include "../include/System.hpp"
#include "../include/Color.hpp"

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

int System::giveUsingID(){
    return data.value({"machine", "using_id"});
}

void System::signUpUser(){
    std::string name, password, confirm, re = " ";

    using_id++, user_count++;

    std::cout << color::pick("> Username: ", "1;33");
    std::cin >> name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    password:
    std::cout << color::pick(">" + re + "Password: ", "1;33");
    password = inputPassword();

    std::cout << color::pick("> Confirm Password: ", "1;33");
    confirm = inputPassword();

    if (password != confirm){
        re = " Retry Your  ";
        goto password;
    }

    data.save({"machine", "using_id"}, using_id);
    data.save({"machine", "user_count"}, user_count);

    data.append({"users"}, {
        {"current_dir", "/home/" + name},
        {"history_file", name + ".history"},
        {"home_dir", "/home/" + name},
        {"id", using_id},
        {"is_admin", false},
        {"name", name},
        {"password_hash", password},
        {"theme", {}}
    });
}

void System::verifyLogin() {
    std::string name, password;

    while (true) { // keep asking username
        std::cout << color::pick("Login as: ", "1;34");
        std::cin >> name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int user_count = data.value({"machine", "user_count"});
        bool user_found = false;

        for (int count = 0; count < user_count; count++) {
            std::string index = std::to_string(count);
            std::string stored_name = data.value({"users", index, "name"});

            if (name == stored_name) {
                user_found = true;

                // Password loop
                while (true) {
                    std::cout << color::pick("Password for " + name + ": ", "1;31");
                    password = inputPassword();

                    std::string stored_pass = data.value({"users", index, "password_hash"});
                    if (password == stored_pass) {
                        data.save({"machine", "using_id"}, count);
                        return; // login successful
                    } else {
                        std::cout << color::pick("Sorry try again", "33") << std::endl;
                    }
                }
            }
        }

        if (!user_found) {
            std::cout << color::pick("Can't find user: " + name, "33") << std::endl;
        }
    }
}

void System::deleteUser(std::string name){
    int not_found = 0;

    for (int count = 1; count <= data.value({"machine", "user_count"}); count++){
        if (name == data.value({"users", std::to_string(count - 1), "name"})){
            data.remove({"users", std::to_string(count - 1)});
            std::cout << "Done for Removing user " << name << std::endl;
            break;
        }else {
            not_found++;
            continue;
        }

        for (int i = 0; i < data.value({"machine", "user_count"}); i++)
            data.save({"users", std::to_string(i), "id"}, i);
    }

    if (not_found == data.value({"machine", "user_count"})){
        std::cout << color::pick("Can't find user: " + name, "33") << std::endl;
    }
}

std::string System::inputPassword() {
    std::string password;
        termios oldt, newt;

        // Disable echo & enable immediate char reading
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        char c;
        while (true) {
            c = getchar();

            if (c == '\n' || c == '\r') { // Enter pressed
                std::cout << '\n';
                break;
            }
            else if (c == 127 || c == 8) { // Backspace
                if (!password.empty()) {
                    password.pop_back();
                    std::cout << "\b \b"; // erase *
                    std::cout.flush();
                }
            }
            else if (isprint(c)) { // Only printable chars
                password.push_back(c);
                std::cout << '*'; // Show *
                std::cout.flush();
            }
            // Ignore other control keys (arrows, etc.)
        }

        // Restore terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return password;
}

System::System(): data("../settings/system.json"){
    raw_data = data.exportString();
    user_count = data.value({"machine", "user_count"});
    using_id = data.value({"machine", "using_id"});

    if (using_id < 0){
        signUpUser();

    }else {
        verifyLogin();
    }
}
