#include <iostream>

#include "include/System.hpp"
#include "include/User.hpp"
// #include "include/Color.hpp"

using namespace std;

int main(){
    std::cout << "\033[1;37mWhite text\033[0m" << std::endl; // bright white
    std::cout << "\033[1;33mBright yellow\033[0m" << std::endl; // bright yellow

    string command;
    bool running = true;

    cout << "\033[37m";

    System os;
    User user(os.giveUsingID());

    // system("clear");

    cout << "Welcome to the mini-Terminal!" << "\n\n";
    user.consoleInterface();
    cin >> command;

    return 0;
}
