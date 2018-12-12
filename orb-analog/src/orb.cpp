#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>
#include <stdint.h>
#include <bitset>
#include <stdlib.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <orb_config.hpp>

#include <utilities.hpp>

using namespace std;

void helper(){
	cout << "Orb Application Analog Version: " << ORB_VERSION << endl <<
	"Gives Analog capabilities to the RPI" << endl <<endl <<
	"Usage: orb analog [options]" << endl << endl <<
	"Options:" << endl <<
	"-h\tprint help" << endl <<
	"-a\taddress (default:0x45)" << endl <<
	"-r\tread analog pin (0 - 15)" << endl << endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	
	bool h = false;
	bool read = false;
	uint8_t pin = 0;
	uint8_t address = 0x45;
	
	static struct option long_options[] = {
		{"help",	no_argument, 0,	'h'},
		{"read",	required_argument, 0,	'r'},
		{"address",	required_argument, 0,	'a'},
		{0,0,0,0}
	};
	int ad = 0;
	while ((opt = getopt_long(argc, argv, "hr:a:",long_options, &option_index)) != -1) {
		switch (opt) {
			case 'a':
				if(strtol(optarg, NULL, 0) > 255){
					cerr << "Wrong input on the address" << endl;
					exit(0);
				}
				address = (uint8_t)strtol(optarg, NULL, 0);
				break;
			case 'r':
				pin = atoi(optarg);
				read = true;
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
	fd = wiringPiI2CSetup(address);


	if(read){
		uint8_t pinByte = getPin(pin);
		wiringPiI2CWriteReg8(fd,pinByte,0x80);
		delay(150);
		uint8_t byte1 = wiringPiI2CRead(fd);
		uint8_t byte2 = wiringPiI2CRead(fd);
		uint8_t byte3 = wiringPiI2CRead(fd);

		if((byte1 >> 7) & (byte2 >> 6) & 0x01){
			cerr << "Analog Overflow : Voltage out of range" << endl;
			exit(0);
		}

		signed int voltage = (((byte1 & 0x03F) << 10) | (byte2 << 2) | (byte3 >> 6))/2;
		cout << voltage << endl;
	}

	return 0;
}
