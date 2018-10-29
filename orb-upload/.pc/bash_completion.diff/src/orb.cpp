#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>

#include <orb_config.hpp>
using namespace std;

void helper(){
	cout << "\nOrb Application Upload Version: " << ORB_VERSION << endl <<
	"Uses Picberry to upload firmwares to the PIC" << endl << endl <<
	"Usage: orb upload [options]" << endl << endl <<
	"Options: " << endl <<
	"-h\t\tprint help" << endl <<
	"-r [output]\tread chip to file [defaults to ofile.hex] " << endl <<
	"-w firmware\tbulk erase, write and check firmware" << endl <<
	"-e\t\terase chip" <<endl <<
	"-b\t\tblank check of the chip" << endl <<
	"-d\t\tread configuration registers" << endl <<
	"--noverify\tskip memory verification after writing" << endl <<
	"--debug\t\tturn on debug" << endl <<endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;

	bool h = false;
	bool invalid = false;

	static struct option long_options[] = {
		{"help",	no_argument, 0, 'h'},
		{"write",	required_argument, 0, 'w'},
		{"read",	required_argument, 0, 'r'},
		{"erase",	no_argument, 0, 'e'},
		{"blank",	no_argument, 0, 'b'},
		{"config",	no_argument, 0, 'd'},
		{"noverify",	no_argument, 0, 1},
		{"debug",	no_argument, 0, 1},
		{0,0,0,0}
	};
	
	while((opt = getopt_long(argc, argv, "hw:r:debc", long_options, &option_index)) != -1) {
		switch(opt){
			case ':':
			case '?':
			case 'h':
				h = true;
				break;
			default:
				h = false;
				break;
		}
	}

	if(h || argc < 2){
		helper();
		return 0;
	}


	string args = "";
	for(int i = 1; i < argc; ++i)
		args += string(argv[i]) + " ";
	system(("picberry -f pic16f150x -g 13,19,26 "+args).c_str());
	return 0;
}
