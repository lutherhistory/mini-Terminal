// C standard headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

// C++ standards headers
#include <iostream>
#include <vector>

// POSIX headers
#include <sys/wait.h>
#include <sys/file.h>
#include <unistd.h>


auto tokenizer(char* data) 
{
	std::vector<char*> args;
	char *token = std::strtok(data, " ");

	while (token != nullptr) {
		args.push_back(token);

		token = std::strtok(nullptr, " ");
	}
	args.push_back(nullptr);

	return args;
}

// @return status.
//	-1: if something has wrong
// 	 0: if nothing
// 	 1: if succeed
auto handle_redirect(std::vector<char*>& args)
{
	for (int i=0; args[i] != nullptr; i++) 
	{
		if (std::string(args[i]) == ">") 
		{
			if (!std::freopen(args[i+1], "w", stdout))
				return -1;

			args[i] = nullptr;
			return 1;
		}
	}

	return 0;
}

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

	if (std::string(args[0]) == "exit")
		exit(EXIT_SUCCESS);

	auto pid 	= fork();

	if (pid < 0) 
	{
		// I'm the failure of forking. (Something weird though btw >D)
		std::cerr << "Failed to load" << std::endl;
		exit(EXIT_FAILURE);
	}

	else if (pid == 0) 
	{
		if (handle_redirect(args) < 0) {
			std::cerr << "mish: Could not redirect" << std::endl;
			_exit(1);
		}

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
		
		std::cout
			<< "~" 
			<< "$ ";
		std::getline(std::cin, buf, '\n');
	
		if (can_parse(buf))
			process(buf, status);
	}

	return 0;
}