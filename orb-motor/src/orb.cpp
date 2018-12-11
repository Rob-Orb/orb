#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>
#include <stdint.h>
#include <bitset>

#include <wiringPiI2C.h>
#include <orb_config.hpp>

#define FUNC_SPEED	0x08
#define FUNC_POS	0x04
#define FUNC_MOTOR	0x02
#define FUNC_TIME	0x01
#define FUNC_READ_ENC	0x10
#define FUNC_READ_STATE	0x20

using namespace std;

void helper(){
	cout << "Orb Application Motor Version: " << ORB_VERSION << endl <<
	"Gives you the power to control the motors" << endl <<endl <<
	"Usage: orb motor [options]" << endl << endl <<
	"Options:" << endl <<
	"-h\tprint help" << endl <<
	"-m\tmotor (0:all - default, 1-2)" << endl <<
	"-d\tdirection (0 : left - 1 : right)" << endl <<
	"-%\tduty cycle (0-100) %" << endl << 
	"-p\tposition control (0-1023)" << endl << 
	"-s\tspeed control (0-1023)" << endl << 
	"-t\ttime running (0-255) s" << endl << 
	"-e\tread encoder" << endl <<
	"-r\tread state" << endl << endl;
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
		{"readencoder",	no_argument, 0,	'e'},
		{"readstate",	no_argument, 0,	'r'},
		{"motor",	required_argument, 0,	'm'},
		{"dir",		required_argument, 0,	'd'},
		{"duty",	required_argument, 0,	'%'},
		{"time",	required_argument, 0,	't'},
		{"position",	required_argument, 0,	'p'},
		{"speed",	required_argument, 0,	's'},
		{0,0,0,0}
	};
	while ((opt = getopt_long(argc, argv, "hrem:d:%:t:p:s:",long_options, &option_index)) != -1) {
		switch (opt) {
			case 'm':
				mo = atoi(optarg);
				if(optarg[0] == '-' || mo > 2){
					cerr << "Wrong input to option m" << endl;
					return 0;
				}
				if(mo == 0)
					mo = 3;
				break;
			case 'd':
				di = atoi(optarg);
				if(optarg[0] == '-' || di > 1){
                                        cerr << "Wrong input to option d" << endl;
                                        return 0;
                                }
				changeDir = true;
				break;
			case 'e':
				func = FUNC_READ_ENC;
				break;
			case 'r':
				func = FUNC_READ_STATE;
				break;
			case '%':
				du = atoi(optarg);
				if(optarg[0] == '-' || du > 100){
                                        cerr << "Wrong input to option %" << endl;
                                        return 0;
                                }
				func |= FUNC_MOTOR;
				break;
			case 'p':
				du = atoi(optarg);
				if(optarg[0] == '-' || du > 1023){
                                        cerr << "Wrong input to option p" << endl;
                                        return 0;
                                }
				func |= FUNC_POS;
				break;
			case 's':
				du = atoi(optarg);
				if(optarg[0] == '-' || du > 1023){
                                        cerr << "Wrong input to option s" << endl;
                                        return 0;
                                }
				func |= FUNC_SPEED;
				break;
			case 't':
				ti = atoi(optarg);
				if(optarg[0] == '-' || ti > 255){
                                        cerr << "Wrong input to option t" << endl;
                                        return 0;
                                }
				func |= FUNC_TIME;
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
		regi |= 1 << 3;
		regi |= di << 2;
	}

	if((func&0x01) == FUNC_TIME){
		regi |= 1 << 4;
		wiringPiI2CWriteReg8(fd, regi, ti);
	}
	regi &= ~(1UL << 4);

	if((func&0X02) == FUNC_MOTOR){
		regi |= 0x02 << 4;
		wiringPiI2CWriteReg8(fd, regi, (uint8_t)(du*2.55));
	}else if((func&0x04) == FUNC_POS){
		regi |= 0x04 << 4;
		wiringPiI2CWriteReg8(fd, regi, (uint8_t)(du/4));
	}else if((func&0x08) == FUNC_SPEED){
		regi |= 0x05 << 4;
		wiringPiI2CWriteReg8(fd, regi, (uint8_t)(du/4));
	}
	regi &= 0x0F;

	if((func&0x10) == FUNC_READ_ENC || (func&0x20) == FUNC_READ_STATE){
		if(mo == 3){
			cerr << "Can only choose one motor" << endl;
			return 0;
		}
		regi |= 0x03 << 4;
		if((func&0x10) == FUNC_READ_ENC){
			wiringPiI2CWriteReg8(fd, regi, 0);
			int result = 0;
			uint8_t rec = wiringPiI2CRead(fd);
			//cout << (int)rec << endl;
			result = rec;
		
			rec = wiringPiI2CRead(fd);
			//cout << (int)rec << endl;
			result |= rec<<8;

			rec = wiringPiI2CRead(fd);
			//cout << (int)rec << endl;
			result |= rec<<16;

			rec = wiringPiI2CRead(fd);
			//cout << (int)rec << endl;
			result |= rec<<24;

			cout << result << endl;
		}
		else if((func&0x20) == FUNC_READ_STATE){
			wiringPiI2CWriteReg8(fd, regi, 0x40);
			int result = 0;
			uint8_t rec = wiringPiI2CRead(fd);
			//cout << (int)rec << endl;
			result = rec;
			
			cout << result << endl;
		}
	}
	return 0;
}
