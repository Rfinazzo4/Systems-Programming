#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "dirent.h"
#include "sys/stat.h"
#include "sys/types.h"

int main(int ac, char* args[])
{
 	if (ac==1 || ac==2){ //check the amount of arguments given
		printf("Synopsis: dirp OPTION FILE [FILE]\n");
		exit(1);
	}
	else{	
			int file;
			if ((strcmp(args[1],"-c"))==0){
				file = mkdir(args[2],S_IRWXU);
				if (file>0){
					printf("Failed to create directory");
				}
			}
			else if ((strcmp(args[1],"-d"))==0){
				DIR* dir;
				dir = opendir(args[2]);
				if (dir==NULL){
					printf("ERROR directory does not exist");
					exit(1);
				}
				
				file = rmdir(args[2]);
				if (file>0){
					printf("File is empty");
				}
			}
			else if ((strcmp(args[1],"-r"))==0){
				file =rename(args[2], args[3]);
				if (file>0){
					printf("Failed to rename directory");
				}
			}
		}
	}
