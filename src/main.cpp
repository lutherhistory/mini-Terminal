#include <cstring>
#include <string>
#include <iostream>
#include <vector>
// #include <filesystem>

#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

// namespace fs = std::filesystem;

void process(std::string& buf, int& status)
{
	pid_t pid 	= fork();

	if (pid < 0) 
	{
		// I'm the failure of forking. (Something weird though btw >D)
		std::cerr << "Failed to fork" << std::endl;
		return;
	}

	else if (pid == 0) 
	{
		// I'm the child.
		std::vector<char*> args;		

		char *token = std::strtok(buf.data(), " ");
		while (token != nullptr) {
			args.push_back(token);

			token = std::strtok(nullptr, " ");
		}

		args.push_back(nullptr);

		if (execvp(args[0], args.data())) {
			std::cerr 
				<< "mnsh: Unknown command: " 
				<< buf
				<< std::endl;

			_exit(127);
		}
	}

	else 
	{
		// I'm the parent.
		waitpid(pid, &status, 0);
	}
}

int main(int argc, char **argv)
{
	_start:

	std::string buf;
	int status = 0;

	std::cout << "$ ";
	std::getline(std::cin, buf, '\n');
	
	if (buf.empty()) goto _start;
	if (buf == "exit") return 0;

	process(buf, status);

	return 0;
}