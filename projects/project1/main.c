#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

//Error Message Functions
void argsError(){
  printf("Error: missing or extra arguments\n");
}

void portError(){
  printf("Error: port number must be in the range of [1024, 65535]\n");
}

void timeError(){
  printf("Error: time argument must be greater than 0\n");
}
/// @brief This function parses the command line arguments and makes sure that they are correct for a server invocation
/// There must be 4 total command line arguments, the program, the -s for server, -p to denote port
/// is next, and the port number itself which must be between 1025 and 65535.

/// @param argc The number of command line arguments, passed in from main
/// @param argv The command line arguments, passed in from main 


int serverCommandParse(int argc, char* argv[]){
  if(argc != 4){
    argsError();
    return -1;
  }
  if(strcmp(argv[2], "-p") != 0){
    argsError();
    return -1;
  }
  if(atoi(argv[3]) < 1024 || atoi(argv[3]) > 65535){
    portError();
    return -1;
  }
  return 0;
}
/// @brief This function parses the command line arguments and makes sure that they are correct for a client invocation
/// There must be 8 total command line arguments, the program, the -c for client, -p to denote port, -h to denote the hostname, the hostname
/// -p to denote port, the port number which must be between 1025 and 65535, -t to denote time, and the time number which must be 0 or greater

/// @param argc The number of command line arguments, passed in from main
/// @param argv The command line arguments, passed in from main 


int clientCommandParse(int argc, char* argv[]){
  if(argc != 8){
    argsError();
    return -1;
  }
  if(strcmp(argv[2], "-h") != 0){
    argsError();
    return -1;
  }
  if(strcmp(argv[4], "-p") != 0){
    argsError();
    return -1;
  }
  if(atoi(argv[5]) < 1024 || atoi(argv[3]) > 65535){
    portError();
    return -1;
  }
  if(strcmp(argv[6], "-t") != 0){
    argsError();
    return -1;
  }
  if(atoi(argv[7]) < 0){
    timeError();
    return -1;
  }
  return 0;
}

/// @brief The main function performs error checking and calls either the client 

/// Client Usage: ./iPerfer -c -h <server_hostname> -p <server_port>
/// Server Usage: ./iPerfer -s -p <listen_port>

/// @param argc 
/// @param argv 
int main(int argc, char* argv[]){
  //Check if the program is being run as a client or server  
  int error_check = 0;
  if(argc < 4){
    argsError();
    return -1;
  }
  //Error check server command line arguments and start server
  if(strcmp(argv[1], "-s") == 0){
    printf("Entering Server Mode\n");
    error_check = serverCommandParse(argc, argv);
    if(error_check == -1){
      return -1;
    } 
    runServer(argv);
  }
  //Error check client command line arguments and start client
  else if(strcmp(argv[1], "-c") == 0){
    printf("Entering Client Mode\n");
    error_check = clientCommandParse();
    if(error_check == -1){
      return -1;
    }
    runClient(argv);
  }
  else{
    argsError();
    return -1;
  }
  return 0;
}

