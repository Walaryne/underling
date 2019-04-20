#include <iostream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

//Global variable needed for the alarm_handler
//Necessisary since you cannot pass (custom) variables to signal handlers
bool exec = false;

//Sets exec to true upon receiving SIGALRM
void alarm_handler(int sig) {
	exec = true;
}

int main(int argc, char **argv) {
	//Define time in seconds variable
	int time;
	//Define character option variable
	char opt;
	//Define "daemonize" variable
	bool daemonize = false;
	//Define usage line
	char *usage = (char *) "Usage: %s [-d] <seconds> <command>\n";

	//Get all options available, currently only -d, if -d is defined, daemonize is true
	//else print usage to stderr and exit with failure status
	while ((opt = getopt(argc, argv, "d")) != -1) {
		switch (opt) {
			case 'd': {
				daemonize = true;
				break;
			}
			default: {
				std::fprintf(stderr, usage, argv[0]);
				std::exit(EXIT_FAILURE);
			}
		}
	}

	//Check to see if we have at least 3 arguments (including argv[0])
	if(argc < 3) {
		std::fprintf(stderr, usage, argv[0]);
		std::exit(1);
	}

	//Try to convert time in seconds argument to an integer
	//If the character is unconvertable, print error and exit with failure status
	try {
		time = std::stoi(argv[optind]);
	} catch(std::invalid_argument) {
		std::fprintf(stderr, "Incorrect time in seconds argument\n");
		std::exit(EXIT_FAILURE);
	}

	//Check if daemonize is true, if so, daemonize the process
	if(daemonize) {
		daemon(1, 0);
	}

	//Set signal handler for SIGALRM to alarm_handler
	std::signal(SIGALRM, alarm_handler);

	//Set an alarm for the user entered time in the future in seconds
	alarm(time);

	//Infinite loop, checks to see if exec is true
	//If exec is true, then execute the command in argv[optind + 1]
	//Else, pause the process until a signal arrives
	for(;;) {
		if(exec) {
			std::system(argv[optind + 1]);
			break;
		}
		pause();
	}

	//Exit with success status
	return EXIT_SUCCESS;
}