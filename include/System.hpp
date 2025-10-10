#pragma once

#include "JSON.hpp"
#include <string>

class System {
private:
    int using_id = 0, user_count = 0;
    bool permission = false;
    std::string raw_data;

    JSON data;

public:
    int giveUsingID();

    void signUpUser();

    void verifyLogin();

    void deleteUser(std::string);

    std::string inputPassword();

    System();
};
