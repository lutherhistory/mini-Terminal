// C standard headers
#include <cstring>
#include <cctype>

// C++ standards headers
#include <iostream>
#include <vector>

// POSIX headers
#include <sys/wait.h>
#include <unistd.h>

bool can_parse(std::string& buf)
{
	for (unsigned char c : buf) {
		if (!std::isspace(c))
			return true;
	}

	return false;
}

void process(std::string& buf, int& status)
{
	char *token = std::strtok(buf.data(), " ");

	if (std::strcmp(token, "exit") == 0) {
		exit(0);
	}

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

		while (token != nullptr) {
			args.push_back(token);

			token = std::strtok(nullptr, " ");
		}

		(args.empty())
		?
			_exit(0)
		:
			args.push_back(nullptr);

		if (execvp(args[0], args.data())) {
			std::cerr 
				<< "mish: Unknown command: " 
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
	int status = 0;

	while (true){
		std::string buf;
	
		std::cout << "$ ";
		std::getline(std::cin, buf, '\n');
	
		if (can_parse(buf))
			process(buf, status);
	}

	return 0;
}