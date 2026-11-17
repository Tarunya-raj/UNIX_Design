#include <iostream>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t signal_received =0;

void signalHandler(int signal)
{
	if(signal == SIGUSR1)
		signal_received =1;
}

int main()
{
	signal(SIGUSR1, signalHandler);
	std::cout<<"Receiver started PID: " << getpid()<<"\n";
	
	while(true)
	{
		if(signal_received)
		{
			signal_received =0;
			std::cout<<"\nReceived SOIGUSR1 ! Reacting\n";
		}
		sleep(1);
	}
	return 0;
}


