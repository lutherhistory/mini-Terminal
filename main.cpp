#include <iostream>

#include "include/System.hpp"
#include "include/User.hpp"
// #include "include/Color.hpp"

using namespace std;

int main(){
    string command;
    bool running = true;

    cout << "\033[37m";

    System os;
    User user(os.giveUsingID());
    system("clear");

    cout << "Welcome to mini-Terminal, the best terminal emulator for Any OS!" << endl;
    cout << "Have fun learning and testing!" << endl;
    cout << "If you need to \'help \', type help for commands" << endl;
    cout << "or you want to report a bug and give feedback, " << endl;
    cout << "github: https://github.com/lutherhistory/mini-Terminal, telegram channel: https://t.me/LHProgramming";
    cout << endl << endl;

    do {
        user.consoleInterface();
        cin >> command;

        if(command == "exit"){
            running = false;
            break;
        }else {

        }
    } while (running);

    return 0;
}
