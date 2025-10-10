#pragma once

#include "JSON.hpp"
#include <string>

class System {
private:
    int using_id = 0, user_count = 0;
    std::string raw_data;

    JSON data;

public:
    void signUpUser();

    void verifyLogin();

    void deleteUser(std::string);

    std::string inputPassword();

    std::string color(const std::string&, const std::string&);

    System();
};
