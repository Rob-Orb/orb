#include <iostream>
#include <errno.h>
#include <string>
#include <getopt.h>

using namespace std;

void helper(){
	cout << "Orb Application Upload :\n
	Uses Picberry to upload firmwares to the PIC" << endl;
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;

	bool h = false;

	static struct option long_option[] = {
		{"help",	no_argument, 0, 'h'}
		{0,0,0,0}
	};
	
	while((opt = getopt_long(argc, argv, "h", long_options, &option_index)) != -1) {
		switch(opt){
			case 'h':
			default:
				h = true;
				break;
		}
	}

	if(h){
		helper();
		system(("picberry -h").c_str());
		return 0;
	}


	string args = "";
	for(int i = 1; i < argc; ++i)
		args += string(argv[i]) + " ";
	system(("picberry -f pic16f150x -g 13,19,26 "+args).c_str());
	return 0;
}
