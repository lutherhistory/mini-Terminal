// C standard headers
#include <cstdlib>
#include <cstring>
#include <cctype>

// C++ standards headers
#include <iostream>
#include <vector>

// POSIX headers
#include <sys/wait.h>
#include <unistd.h>

auto tokenizer(char* data) {
	std::vector<char*> args;

	char *token = std::strtok(data, " ");

	while (token != nullptr) {
		args.push_back(token);
		
		if (std::strcmp(args[0], "exit") == 0) {

			exit(0);
		}

		token = std::strtok(nullptr, " ");
	}
	args.push_back(nullptr);

	return args;
}

// auto handle_redirect(std::vector<char*>& args)
// {

// 	return 0;
// }

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
	auto args 	= tokenizer(buf.data());		
	auto pid 	= fork();


	if (pid < 0) 
	{
		// I'm the failure of forking. (Something weird though btw >D)
		std::cerr << "Failed to load" << std::endl;
		exit(EXIT_FAILURE);
	}

	else if (pid == 0) 
	{
		// I'm the child.
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
	if (argc < 1) (void) argc, (void) argv;

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