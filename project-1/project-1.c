#include <stdio.h>

int main(int argc, char **argv)
{
	printf("Jed Dunn\nCNS3060\n");
	
	int i;
	if(argc > 1)
	{
		//Skips argument 0 since it is just the program name.
		for(i = 1; i < argc; i++)
		{
			printf("%s\n",argv[i]);	
		}
	}
	else
		printf("No command line arguments given.");


	return 0;
}
