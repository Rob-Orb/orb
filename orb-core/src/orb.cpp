#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <getopt.h>

#include <orb_config.hpp>
using namespace std;

void helper(){
	cout << "\nOrb Core Version : " << ORB_VERSION << endl << endl <<
	"Usage: orb [application]\n\n";
}

int main(int argc, char *argv[])
{
	if(argc < 2 || argv[1][1] == 'h'){
		helper();
		return 0;
	}

	const char* pathT = getenv("ORB_PATH");
	if(pathT == NULL){
		cout << "Don't forget to execute :\nsource /opt/orb/setup.bash\n" << endl;
		return 0;
	}
	string path(pathT);
	string args = "";
	for(int i = 1; i < argc; ++i)
		args += string(argv[i]) + " ";
	system((path+args).c_str());

	return 0;
}
