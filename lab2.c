/* -------------------------------------------------------
	Lab2
	
	Name: lab2.c
	
	Purpose: This is a C Program that passes a file from the command line
			and outputs the file into reverse order.
	
	Description of parameters:
			argv[1] the input file
			argv[2] the file to be written
			
	Libraries included: 
			#include <stdio.h>
			#include <string.h>

---------------------------------------------------------**/


#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[]){

	FILE *input;
    	FILE *out;
 
    	int counter = 0;
    	int i   = 0;
     
	// check to  see if there are enough arguments

    	if( argc < 3 )
   	{
        	printf("You need to add more arguments to the command line\n");
        	return -1;
    	}
	
	//opens input file     
	input = fopen(argv[1],"r");
	
	if( input == NULL )
	{
		printf("\n%s File can not be opened : \n",argv[1]);
		return -1;
	}
	
	//opens file that is going to be written to
	out = fopen(argv[2],"w");
   
	 if( out == NULL )
	{
        	printf("\n%s File can not be opened : \n",argv[2]);
        	return -1;
    	}
     
	//moves the file pointer to the end.
 	 fseek(input,0,SEEK_END);
 
	//get the position of file pointer.
    	counter = ftell(input);

	while( i < counter )
    	{
        	i++;
        	//finds the end ofinput character
		fseek(input,-i,SEEK_END);

       		//prints character from input andd writes to out
		fprintf(out,"%c",fgetc(input));
    	}
   
	printf("\nFile has been reversed!\n");

	fclose(input);
    	fclose(out);
 

    return 0;
}
