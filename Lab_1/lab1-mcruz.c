#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Lab Assignment 1
Miguel Cruz 
CSC 322
*/
void encrypt_message(char message[]){ 

char ch = message; 
int key = 5; 

for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= '~'){
			ch = ch + key;
			
			if(ch > '~'){
				ch = ch - '~' + 'a' - 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= '`'){
			ch = ch + key;
			
			if(ch > '`'){
				ch = ch - '`' + 'A' - 1;
			}
			
			message[i] = ch;
		}
   	else if(ch >= ' ' && ch <= '@'){
			ch = ch + key;
			
			if(ch > '@'){
				ch = ch - '@' + ' ' - 1;
			}
			
			message[i] = ch;
		}
	}
	
	printf("Encrypted message: %s\n", message); 
  main();

}

void decrypt_message(char message[]){ 
  char ch = message; 
  int key = 5; 
	for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= '~'){
			ch = ch - key;
			
			if(ch < 'a'){
				ch = ch + '~' - 'a' + 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= '`'){
			ch = ch - key;
			
			if(ch < 'A'){
				ch = ch + '`' - 'A' + 1;
			}
			
			message[i] = ch;
		}
    else if(ch >= ' ' && ch <= '@'){
			ch = ch - key;
			
			if(ch < ' '){
				ch = ch + '@' - ' ' + 1;
			}
			
			message[i] = ch;
		}
	}
	
	printf("Decrypted message: %s\n", message);
	main(); 
}

int main() {
   	// A 16KB buffer should be enough for any message 
    // message != essay 
    char message[16*1024];
    
    // User inputs command
    printf("mcruz$ "); 
    fgets(message, sizeof(message), stdin); 
    printf("You entered: %s\n", message); 
    
  // Store user input in an array of strings as token using () as a splitting delimiter
  // Limitation of this implementation is that it will break with messages containing a "(" or ")" within it
  // since those are my delimiters
  char * token;
  token = strtok (message," ()");
  int index = 0;
  char *token_list[3];

  while (token != NULL){
    token_list[index] = token;   
    printf ("%d: %s\n",index, token);
    token = strtok (NULL, "()");
    index++; 
  }

  //Error handling to prevent typos from users
  if(strcmp(message,"exit\n") == 0){ 
      printf("Exiting...\n"); 
      exit(0); 
  }

  if(strcmp(token_list[0], "decrypt") == 0){ 
     decrypt_message(token_list[1]); 
  }
  else if(strcmp(token_list[0], "encrypt") == 0){
     encrypt_message(token_list[1]); 
}
  else if(strcmp(token_list[0], "encrypt") !=0){ 
      printf("[ERROR] Please enter the command correctly!!!\n"); 
      main(); 
}
  else if(strcmp(token_list[0], "decrypt") !=0){ 
      printf("[ERROR] Please enter the command correctly!!!\n"); 
      main(); 
}

    return 0; 
}






