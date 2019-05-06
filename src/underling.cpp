#include <iostream>
#include <cstdlib>
#include <csignal>
#include <chrono>
#include <unistd.h>

#define MAJOR 1
#define MINOR 1
#define PATCH 0

//Global variable needed for the alarm_handler
//Necessary since you cannot pass (custom) variables to signal handlers
bool exec = false;

//Sets exec to true upon receiving SIGALRM
void alarm_handler(int sig) {
	exec = true;
}

int main(int argc, char **argv) {
	//Define time in seconds variable
	double time = 0;
	//Define character option variable
	char opt;
	//Define "daemonize" variable
	bool daemonize = false;
	//Define "dumptime" variable
	bool dumptime = false;
	//Define usage line
	char *usage = (char *) "Usage: %s [-dvhYMDHmS] <command>\n";
	//Define help line
	char *help = (char *) "OPTIONS:\n" \
						"\t-d,\tDaemonize the process\n"\
						"\t-v,\tPrint version and exit\n"\
						"\t-h,\tPrint this help text and exit\n"\
						"\t-t,\tDump the time in seconds till execution\n"\
						"\t-Y,\tAdd X years to execution time\n"\
						"\t-M,\tAdd X months to execution time\n"\
						"\t-D,\tAdd X days to execution time\n"\
						"\t-H,\tAdd X hours to executon time\n"\
						"\t-m,\tAdd X minutes to execution time\n"\
						"\t-S,\tAdd X seconds to execution time\n";

	//Get all options available; if -d is defined, daemonize is true
	//If -v is defined, print version and exit
	//If -h is defined, print help and exit
	//If -YMDHm or S are defined, update the time to reflect Years, Months, Days, Hours, Minutes, or Seconds respectively
	//else print usage to stderr and exit with failure status
	while ((opt = getopt(argc, argv, "dvhtY:M:D:H:m:S")) != -1) {
		switch (opt) {
			case 'd': {
				daemonize = true;
				break;
			}
			case 'v': {
				std::fprintf(stderr, "Underling %d.%d.%d\n", MAJOR, MINOR, PATCH);
				std::exit(EXIT_SUCCESS);
			}
			case 'h': {
				std::fprintf(stderr, usage, argv[0]);
				std::fprintf(stderr, "%s", help);
				std::exit(EXIT_SUCCESS);
			}
			case 't': {
				dumptime = true;
				break;
			}
			case 'Y': {
				time += (std::stod(optarg) * 31536000);
				break;
			}
			case 'M': {
				time += (std::stod(optarg) * 2592000);
				break;
			}
			case 'D': {
				time += (std::stod(optarg) * 86400);
				break;
			}
			case 'H': {
				time += (std::stod(optarg) * 3600);
				break;
			}
			case 'm': {
				time += (std::stod(optarg) * 60);
				break;
			}
			case 'S': {
				time += (std::stod(optarg));
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

	//Check if daemonize is true, if so, daemonize the process
	if(daemonize) {
		daemon(1, 0);
	}

	//Set signal handler for SIGALRM to alarm_handler
	std::signal(SIGALRM, alarm_handler);

	//Set an alarm for the user entered time in the future in seconds
	alarm(time);
	//If dumptime variable is defined, dump the time till execution in seconds
	std::fprintf(stderr, "%f\n", time);

	//Infinite loop, checks to see if exec is true
	//If exec is true, then execute the command in argv[optind + 1]
	//Then, break from the loop and hit the return statement
	//Else, pause the process until a signal arrives
	while(true) {
		if(exec) {
			std::system(argv[optind]);
			break;
		}
		pause();
	}

	//Exit with success status
	return EXIT_SUCCESS;
}
