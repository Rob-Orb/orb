#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <orb_config.hpp>

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout,"%s Version %s\n", argv[0],
				ORB_VERSION);
		return 1;
	}

	double inputValue = atof(argv[1]);

	double outputValue = sqrt(inputValue);
	fprintf(stdout,"The square root of %g is %g\n",inputValue, outputValue);
	return 0;
}

