#include <iostream>
#include <errno.h>
#include <string>
#include <wiringPiI2C.h>

using namespace std;

int main(int argc, char *argv[])
{
	int fd, result;
	fd = wiringPiI2CSetup(0x04);
	cout << wiringPiI2CRead(fd) << endl;

	//wiringPiI2CWriteReg8(fd, 0x01, 0x00);
	return 0;
}
