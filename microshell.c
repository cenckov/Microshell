#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define YELLOW 33
#define CYAN 36
#define WHITE 0

void commands_list();
void welcome();
void reset();
  
char path[255];

int main() {
	
   char command[256];
   char tokens[256][256];
   int i=0;
   int l=1;

   	welcome();
   	
   	printf("%c[%dm",0x1B,CYAN);
   	printf("Logged as: %s\n\n", getlogin());
   	reset();
   	
	while(1){
		
		//Clear table with tokens
		int j = 0;
		
		for(i=0; i<256; i++){
			
			for (j=0;j<256;j++)
				tokens[i][j]='\0';
		}
	   
	   //Get current working path
	   if (getcwd(path, sizeof(path)) != NULL) {
	   	
	   		printf("%c[%dm",0x1B,CYAN);
	   		printf("[%d] ",l);
	   		reset();
	       	printf("%s$ ", path);
         
         
        //Get tokens from command
	       	strtok(fgets(command,256,stdin), "\n");
	   
	        int k = 0;
	        int j = 0;
         
	        for(i=0;i<256;i++){

	       	if (command[i]==' '){
	       		
	       		tokens[k][j]='\0';
	       		k++;
	       		j=0;
	       		
			   }
			   
			else{
				
				tokens[k][j]=command[i];
				j++;
			}   
		   }
			
		//main function
	       commands_list(tokens[0],tokens[1], tokens[2]);
	       l++;
	    
	    //if Path not loaded
	   } else {
	       perror("Path load error");
	       return 1;
	   }
}
	   return 0;
}

void commands_list(char *command, char *param, char *param2){

	if(strcmp(command,"cd")==0)
		chdir(param);	
		
	else if (strcmp(command,"exit")==0)
		exit(0);
	
	else if(strcmp(command,"echo")==0)
		printf("%s %s\n", param,param2);

	else if(strcmp(command,"clear")==0)
		write(1, "\33[H\33[2J", 7);

	else if(strcmp(command,"ls")==0){
		
		DIR *dir;
		
		struct dirent *ent;
		
		if ((dir = opendir(getcwd(path, sizeof(path)))) != NULL) {
			
  			while ((ent = readdir (dir)) != NULL) {
  				
				struct stat buf;
				
      			if(ent->d_type == DT_DIR){
      				
      				printf("%c[%dm",0x1B,YELLOW);
      				printf ("%s\n", ent->d_name);
      				printf("%c[%dm",0x1B,WHITE);
      				
				  }
				else printf ("%s\n", ent->d_name);
    			
  		}
  		printf("\n");
  		closedir (dir);
		}		
	}
	
	else if(strcmp(command,"help")==0){

		printf("%s","\nList of commands:\n\n"
		"cd:      cd [DIR] Change the current directory to DIR\n\n"
		"clear:   Clear the terminal screen\n\n"
		"echo:    echo [STRING] Write the STRING argument to the standard output\n\n"
		"exit:    Exit shell\n\n"
		"help:    Show help\n\n"
		"ls:      List directory contents\n\n");
		 
		printf("%c[%dm",0x1B,CYAN);
		printf("%s","+-+-+-+-+-+-+-+-+-+-+\n"
		"|M|i|c|r|o|s|h|e|l|l|\n"
		"+-+-+-+-+-+-+-+-+-+-+\n" );
		puts("Operating systems coursework 2019\nAuthor: A. Cencek\n");
		printf("%c[%dm",0x1B,WHITE);	
	}

	else printf("Unknown command\n");
}

void welcome(){
	printf("%c[%dm ",0x1B,CYAN);
	printf("%s","__  __ _                    _          _ _\n"
        "|  \\/  (_) ___ _ __ ___  ___| |__   ___| | |\n"
        "| |\\/| | |/ __| '__/ _ \\/ __| '_ \\ / _ \\ | |\n" 
        "| |  | | | (__| | | (_) \\__ \\ | | |  __/ | |\n"
        "|_|  |_|_|\\___|_|  \\___/|___/_| |_|\\___|_|_|\n\n");
    printf("%c[%dm ",0x1B,WHITE);
}

void reset()
{
  printf("%c[%dm",0x1B,0);
}
