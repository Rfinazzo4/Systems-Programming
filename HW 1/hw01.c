#include "stdio.h"
#include "stdlib.h"

int main(int ac, char* args[])
{
    	if (ac!=4){
		printf("prec    CHAR    ROWS     COLS \n");
		exit(1);
	}
	double b = atof (args[2]);
	double c = atof (args[3]);
	int i;
	for (i=0; i<b; i++){
		int j;
		for (j=0; j<c; j++){
			printf("%s", args[1]);
		}
		printf("\n");	
	}
return 0;
}