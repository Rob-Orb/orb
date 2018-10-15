#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>
#include <stdint.h>

#include <wiringPiI2C.h>


using namespace std;

void helper(){
	cout << "Orb Application Motor\n
	Gives you the power to control the motors\n\n
	Usqge: orb motor [options]\n\n
	Options:\n
	-m\tmotor (0:all - default, 1-2)\n
	-d\tduty cycle (0-100)%" << endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	
	int du = 10000;
	int mo = 0;
	
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
                                        cerr << "Wrong input to option d" << end
l;
                                        return 0;
                                }
				break;
			case 'h':
			default:
				helper();
				break;
		}
	}
	int fd, result;
	fd = wiringPiI2CSetup(0x04);

	if(mo < 101)
		wiringPiI2CWriteReg8(fd, 0x02, mo);
	if(du < 101)
		wiringPiI2CWriteReg8(fd, 0x01, uint8_t(du*2.55));
	return 0;
}
