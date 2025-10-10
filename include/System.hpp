#pragma once

#include "JSON.hpp"
#include <string>
#include <termios.h>
#include <unistd.h>

class System {
private:
    int id = 0;
    std::string raw_data;

    JSON data;

public:
    void signUpUser();

    void verifyLogin();

    void deleteUser();

    std::string color(const std::string& text, const std::string& code);

    System();
};
