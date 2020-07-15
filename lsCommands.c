/* ----
	Lab3
	
	Name: lsCommands.c
	
	Purpose: This is a C Program that passes a directory path and various ls commands
			use function to generate appropriate output
			-i = displays inode number
			-p = displays protection mask
			-a = access time stamp format: yyyy-mm-dd hh:mm:ss 
			-m = last modified time format: yyyy-mm-dd hh:mm:ss 
			-s #####: Only list files which are smaller than the specified number.
			-b #####: Only list files which are bigger than the specified amount. 
			-d: specifies that directories should show up in the listing
			directory_path = last argument if path is not there assume cwd
			
	
	Description of parameters:
			
                        -i = displays inode number
                        -p = displays protection mask
                        -a = access time stamp format: yyyy-mm-dd hh:mm:ss
                        -m = last modified time format: yyyy-mm-dd hh:mm:ss
                        -s #####: Only list files which are smaller than the specified number.
                        -b #####: Only list files which are bigger than the specified amount.
                        -d: specifies that directories should show up in the listing
                        directory_path = last argument if path is not there assume cwd
			
	Libraries included: 
			#include <stdio.h>
			#include <stdlib.h>
			#include <string.h>
			#include <getopt.h>
			#include <dirent.h>
			#include <sys/types.h>
			#include <sys/stat.h>
			#include <unistd.h>
			#include <time.h>


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


static char perms_buff[30];
const char *get_perms(mode_t mode);

int main(int argc, char* argv[])    {

        DIR *directory;
        struct dirent *dir;
	struct stat myStat;
        struct tm *time;
        char title[40];
	char datestring[256];        
	int opt, size, iFlag, pFlag, aFlag, mFlag, counter;
	int small = 0;
	int big = 0;

	while ((opt = getopt(argc, argv, "ipamsbf:" )) != -1){
		switch(opt){
				case 'i':
						iFlag = 1;
						strcat(title, "Inode   ");
						break;
				case 'p':
						pFlag = 1;
						strcat(title, "Permissions  ");
						break;
				case 'a':
						aFlag = 1;
						strcat(title, "Date Accessed        ");
						break;
				case 'm':
						strcat(title, "Modification Date    ");
						mFlag = 1;
						break;
				case 's':
						/*only files smaller than the following number*/
						small = atoi(argv [optind]);
						printf("%d\n ", small);
						break;
				case 'b':
						/*only files bigger than the following number*/
						big = atoi(argv [optind]);
						printf("%d\n", big);
						break;
				default:
						printf("Error\n");
			}
		}

        // finding the directory in the last argument
        //using current directory if last argument doesn't return 
		
        	if ((directory = opendir(argv[argc-1])) ==NULL)
		{
			if( (directory = opendir(".")) == NULL ) {
			fprintf( stderr, "Cannot open dir\n" );
			}
		}       
		else
		{  //change path
			chdir(argv[argc-1]);
			if( (directory = opendir(".")) == NULL ) {
			fprintf( stderr, "Cannot open dir\n" );
			}
		}

		strcat(title, "Size     Filename ");
		printf("%s\n", title);
		
		//prints out all the things
		
		while( (dir = readdir(directory)) != NULL ){
	
		if (stat(dir->d_name, &myStat)== -1)
			continue;
 		
		size = (int)myStat.st_size;
				
		//prints outfiles that are smaller than "small"
		if((size < small)||(small == 0)) 
		{
			// prints out files that are bigger than "big" 
	           if((size > big)||(big == 0))
			{
			if(iFlag==1)
			{
				//Print Out Inode
				printf("%d   ",(int)myStat.st_ino);
			}
			if(pFlag==1)
			{
				//Print Out Permissions
				printf("  %s  ",get_perms(myStat.st_mode));
			}

			if(aFlag==1)
			{
				//Print Out Accessed Date
				time = localtime(&myStat.st_atime);
				strftime(datestring, sizeof(datestring),"%Y-%m-%d %H:%M:%S", time);
    				printf("  %s   ", datestring);
			}
                        if(mFlag==1)
                        {
                                //Print Out modified Date
                                time = localtime(&myStat.st_mtime);
                                strftime(datestring, sizeof(datestring),"%Y-%m-%d %H:%M:%S", time);
                                printf("  %s  ", datestring);
                        }

			/* Print size of file. */
			printf(" %5d", (int)myStat.st_size);
			printf( " %s\n", dir->d_name );
			counter ++;
			}
		}
		}
	
	printf("%d Directory Entries found\n", counter);
	
	closedir(directory);
	return 0;
}

// get permissions 
const char *get_perms(mode_t mode)
{
	char ftype = ' ';
	sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c", ftype,
  	mode & S_IRUSR ? 'r' : '-',
  	mode & S_IWUSR ? 'w' : '-',
  	mode & S_IXUSR ? 'x' : '-',
  	mode & S_IRGRP ? 'r' : '-',
 	mode & S_IWGRP ? 'w' : '-',
  	mode & S_IXGRP ? 'x' : '-',
 	mode & S_IROTH ? 'r' : '-',
  	mode & S_IWOTH ? 'w' : '-',
 	mode & S_IXOTH ? 'x' : '-');

  	return (const char *)perms_buff;
}
