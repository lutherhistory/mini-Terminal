#include <iostream>
#include <string>

int main(int argc, char **argv) 
{
	while (true) {
		std::string buf;

		std::cout << "$ ";
		std::getline(std::cin, buf, '\n');

		if (buf.empty()) 
			continue;
		
		else if (buf == "exit") 
			return 0;

		std::system(buf.c_str());
	}
}