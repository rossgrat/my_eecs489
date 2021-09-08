#include "server.h"


/// @brief This function sets the socket options and binds the socket to the address

/// This function creates the server socket, and binds the socket to an addr (?), then begins listening on that socket
int setupMyServerSocket(struct myServer* s_ptr, int argv_3){
  //Set port for server
  s_ptr->s_port = argv_3;
  
  //Setup socket for server and do error checking
  s_ptr->s_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(s_ptr->s_socket == -1){
    printf("Error: bad socket\n");
    return -1;
  }

  int ok = 1;  
  if(setsockopt(s_ptr->s_socket, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok)) == -1){
    printf("Error: bad setsockopt\n");
    return -1;
  }
  
  s_ptr->s_addr_len = (socklen_t)sizeof(s_ptr->s_addr);
  memset(&s_ptr->s_addr, 0, s_ptr->s_addr_len);
  s_ptr->s_addr.sin_family = AF_INET;
  s_ptr->s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_ptr->s_addr.sin_port = htons(s_ptr->s_port);

  if(bind(s_ptr->s_socket, (const struct sockaddr*) &s_ptr->s_addr, s_ptr->s_addr_len) == -1){
    printf("Error: bad bind\n");
    return -1;
  }

  if(listen(s_ptr->s_socket, 10) == -1){
    printf("Error: bad listen\n");
    return -1;
  }
  return 0;
}

///@brief This function waits for and accepts conenctions to the server socket
///
///
///

int acceptOnMyServer(struct myServer* s_ptr){

  while(1){
  

  }

}

///@brief This is the main server running loop
///
///@param argv The command line arguments, used here to get the server port

int runMyServer(char* argv[]){
  //Create myServer struct
  struct myServer my_server;
  struct myServer* my_server_ptr = &my_server;
  
  if(setupMyServerSocket(my_server_ptr, atoi(argv[3])) == -1){
    printf("Error: server setup\n");
    return -1;
  }


  printf("myServer.port = %i", my_server.s_port);
}
