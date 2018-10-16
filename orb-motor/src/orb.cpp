#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>
#include <stdint.h>

#include <wiringPiI2C.h>
#include <orb_config.hpp>

using namespace std;

void helper(){
	cout << "Orb Application Motor Version: " << ORB_VERSION << endl <<
	"Gives you the power to control the motors" << endl <<endl <<
	"Usage: orb motor [options]" <<endl <<endl <<
	"Options:" << endl <<
	"-h\tprint help" << endl <<
	"-m\tmotor (0:all - default, 1-2)" <<endl <<
	"-d\tduty cycle (0-100)%" << endl << endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	
	int du = 10000;
	int mo = 0;
	bool h = false;
	
	static struct option long_options[] = {
		{"help",	no_argument, 0,	'h'},
		{"motor",	required_argument, 0,	'm'},
		{"duty",	required_argument, 0,	'd'},
		{0,0,0,0}
	};
	while ((opt = getopt_long(argc, argv, "hm:d:",long_options, &option_index)) != -1) {
		switch (opt) {
			case 'm':
				mo = atoi(optarg);
				if(optarg[0] == '-' || mo > 100){
					cerr << "Wrong input to option m" << endl;
					return 0;
				}
				break;
			case 'd':
				du = atoi(optarg);
				if(optarg[0] == '-' || du > 100){
                                        cerr << "Wrong input to option d" << endl;
                                        return 0;
                                }
				break;
			case 'h':
			default:
				h = true;
				break;
		}
	}

	if(h || argc < 2){
		helper();
		return 0;
	}

	int fd, result;
	fd = wiringPiI2CSetup(0x04);

	if(mo < 101)
		wiringPiI2CWriteReg8(fd, 0x02, mo);
	if(du < 101)
		wiringPiI2CWriteReg8(fd, 0x01, uint8_t(du*2.55));
	return 0;
}
