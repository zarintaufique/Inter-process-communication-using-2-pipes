#include<unistd.h>
#include <sys/shm.h>
#include <string>
#include <stdio.h>
#include <cstring>
#include<sys/types.h>
#include<sys/wait.h>


void change_string(char sentence[]){
    for(int i = 0;sentence[i] != '\0'; i++){
        //upper case
		if(sentence[i] >= 65 && sentence[i] <= 90) { 
            sentence[i] = sentence[i] + 32; 
        }
		//lower case
        else if(sentence[i] >= 97 && sentence[i] <= 122) { 
            sentence[i] =sentence[i] - 32;
        }
    }
}

int main() {
    int p1[2];
    int p2[2]; 
    char sentence[500];
    int pid = fork();
    printf("Enter string: ");
    scanf("%s", sentence);
    
    if (pipe(p1) < 0) {
       printf("Error!\n");
       exit(0);
    }
   
    if (pipe(p2) < 0) {
      printf("Error!\n");
      exit(0);
    }
  
    //child  
    if(pid == 0){ 
		close(p1[1]); 
		close(p2[0]); 
   
        char str[500];
        read(p1[0], str, 500);
        change_string(str);
        write(p2[1], str, strlen(str));
    }
	// Parent process
    else if(pid > 0){ 
		char result[500];
		close(p1[0]); 
		close(p2[1]); 

		write(p1[1], sentence, strlen(sentence));	
		read(p2[0], result, strlen(result)); 		
		printf("Final result : %d", result);
    }
    
   return 0;
}
