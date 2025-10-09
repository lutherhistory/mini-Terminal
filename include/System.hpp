#pragma once

#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class System {
    private:
        std::string user="user", path="~", password;
        std::string file_name = "/home/luther/Workspace/mini-Terminal/resource/system.json";
        std::fstream file;
        json data = {
            {"user", "user"},
            {"password", ""},
            {"path", ""}
        };

    public:
        void renderPath();
        void set();
        void get(std::string);
        void update();

        System();
};
