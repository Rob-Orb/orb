#include <iostream>
#include <errno.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string args = "";
	for(int i = 1; i < argc; ++i)
		args += string(argv[i]) + " ";
	system(("picberry -f pic16f150x -g 13,19,26 "+args).c_str());
	return 0;
}
