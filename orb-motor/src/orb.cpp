#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>

#include <wiringPiI2C.h>


using namespace std;

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	
	int du = 10000;
	int mo = 10000;
	
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
				break;
			case 'd':
				du = atoi(optarg);
				break;
			case 'h':
			default:
				break;
		}
	}
	int fd, result;
	fd = wiringPiI2CSetup(0x04);

	if(mo < 100)
		wiringPiI2CWriteReg8(fd, 0x02, mo);
	if(du < 255)
		wiringPiI2CWriteReg8(fd, 0x01, du);
	return 0;
}
