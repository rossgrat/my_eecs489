#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

/// @brief The main function performs error checking and calls either the client 

/// Client Usage: ./iPerfer -c -h <server_hostname> -p <server_port>
/// Server Usage: ./iPerfer -s -p <listen_port>

/// @param argc 
/// @param argv 


int main(int argc, char* argv[]){
  
  if(strcmp(argv[1], "-s") == 0){
    printf("Entering Server Mode\n");
  }
  if(strcmp(argv[1], "-c") == 0){
   printf("Entering Client Mode\n");
  }

}

void serverCommandParsing(){
  

}
void clientCommandParsing(){ 


}
