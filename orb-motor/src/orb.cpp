#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>
#include <stdint.h>
#include <bitset>

#include <wiringPiI2C.h>
#include <orb_config.hpp>

#define FUNC_MOTOR 2
#define FUNC_TIME 1
#define FUNC_READ 3

using namespace std;

void helper(){
	cout << "Orb Application Motor Version: " << ORB_VERSION << endl <<
	"Gives you the power to control the motors" << endl <<endl <<
	"Usage: orb motor [options]" << endl << endl <<
	"Options:" << endl <<
	"-h\tprint help" << endl <<
	"-m\tmotor (0:all - default, 1-2)" << endl <<
	"-d\tdirection (0:default, 0 : left - 1 : right)" << endl <<
	"-%\tduty cycle (0-100)%" << endl << 
	"-t\ttime running (0-255)s" << endl << 
	"-r\tread encoder (1,2)" << endl << endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	
	bool changeDir = false;
	int func = 0;

	int du = 10000;
	int di = 0;
	int mo = 0;
	int re = 10;
	int ti = 1;
	bool h = false;
	
	static struct option long_options[] = {
		{"help",	no_argument, 0,	'h'},
		{"motor",	required_argument, 0,	'm'},
		{"dir",		required_argument, 0,	'd'},
		{"duty",	required_argument, 0,	'%'},
		{"time",	required_argument, 0,	't'},
		{"read",	required_argument, 0,	'r'},
		{0,0,0,0}
	};
	while ((opt = getopt_long(argc, argv, "hm:d:%:t:r:",long_options, &option_index)) != -1) {
		switch (opt) {
			case 'm':
				mo = atoi(optarg);
				if(optarg[0] == '-' || mo > 3){
					cerr << "Wrong input to option m" << endl;
					return 0;
				}
				break;
			case 'd':
				di = atoi(optarg);
				if(optarg[0] == '-' || di > 1){
                                        cerr << "Wrong input to option d" << endl;
                                        return 0;
                                }
				changeDir = true;
				break;
			case 'r':
				re = atoi(optarg);
				if(optarg[0] == '-' || re > 2){
					cerr << "Wrong input to option r" << endl;
					return 0;
				}
				func = 3;
				break;
			case '%':
				du = atoi(optarg);
				if(optarg[0] == '-' || du > 100){
                                        cerr << "Wrong input to option %" << endl;
                                        return 0;
                                }
				func = 2;
				break;
			case 't':
				ti = atoi(optarg);
				if(optarg[0] == '-' || ti > 255){
                                        cerr << "Wrong input to option t" << endl;
                                        return 0;
                                }
				func = 1;
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

	uint8_t regi = 0;

	regi = mo;
	if(changeDir){
		if(mo != 0){
			regi |= 1 << (mo*2+1);
			regi |= di << ((mo-1)*2+2);
		}else{
			regi |= (0x05 << 3);
			regi |= di << 2;
			regi |= di << 4;
		}
	}

	if(func > 0)
		regi |= func << 6;
	switch(func){
		case FUNC_MOTOR:
		wiringPiI2CWriteReg8(fd, regi, du);
			break;
		case FUNC_TIME:
		wiringPiI2CWriteReg8(fd, regi, ti);
			break;
		case FUNC_READ:
		wiringPiI2CWriteReg8(fd, regi, re);
		cout << wiringPiI2CRead(fd) << endl;
			break;
		default:
			break;
	}
	return 0;
}
