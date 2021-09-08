#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>



struct myServer{
  //Server Information
  int s_port;
  int s_socket;
  
  //Legacy values? Required for bind
  struct sockaddr_in s_addr;
  socklen_t s_addr_len;

  // Information for client when client has connected to the server
  struct sockaddr_in c_addr;
  socklen_t c_addr_len;
  uint32_t c_ip;
  uint32_t c_port;
  char c_name[100];

  //Function pointers for server
  //in (*setupMyServerSocket)();
};
