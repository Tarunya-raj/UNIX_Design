#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout<<"Ussage: ./sender <PID>\n";
		return 1;
	}
	pid_t receiver_pid = std::atoi(argv[1]);

	if(kill(receiver_pid, SIGUSR1) == -1)
	{
		perror("kill");
		return 1;
	}
	std::cout<<"Signal sent successful\n";
	return 0;
}

