#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

//Timing
#include <time.h>

struct myServer{
  //Server information
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
  
  //Connection
  int connfd;
  uint8_t s_buffer[1000];
  ssize_t s_total_recvd;

  // Timing
  time_t start_time;
  time_t end_time;

  //Function pointers for server
  //int (*setupMyServerSocket)();
};

struct myClient{
  //Client information
  int c_port;
  int c_socket;
  char c_hostname[1000];

  //Timing
  time_t c_start_time;
  int c_runtime;

  //Legacy values? Required for connect
  struct sockaddr_in c_addr;
  socklen_t c_addr_len;

  //Server connection information
  struct hostent* s_host;

  //Packet Information
  uint8_t data_packet[1000];
  uint8_t fin_packet[1000];

  //Recieve ACK
  char ack_buffer[4];
};

//Server functions
int runMyServer(char**);

//Client function
int runMyClient(char**);