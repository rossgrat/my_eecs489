#include "header.h"

#define PACKET_BYTE 0x00
#define FIN_BYTE 0xFF

///@brief This function sets up and connects the client socket
///
///@param c_ptr Pointer to myClient object with important connectivity information
///@param hostname The hostname specified in the command line arguments
///@param port The client port to connec to specified in the command line arguments
///@param runtime The time the client will send 1000 byte packets for
int setupMyClientSocket(struct myClient* c_ptr, char hostname[1000], int port){
  //Copy values into client struct
  c_ptr->c_port = port;
  strcpy(c_ptr->c_hostname, hostname);

  //Create client socket
  c_ptr->c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(c_ptr->c_socket == -1){
      printf("Error: bad socket\n");
      return -1;
  }
  
  c_ptr->c_addr.sin_family = AF_INET;

  //Get address of the server from the hostname
  c_ptr->s_host = gethostbyname(c_ptr->c_hostname);
  if (c_ptr->s_host == NULL){
    printf("Error: bad hostname\n");
    return -1;
  }
  memcpy(&(c_ptr->c_addr.sin_addr), c_ptr->s_host->h_addr, c_ptr->s_host->h_length);
  c_ptr->c_addr.sin_port = htons(c_ptr->c_port);

  //Connect to server
  if (connect(c_ptr->c_socket, (struct sockaddr *)&(c_ptr->c_addr), sizeof(c_ptr->c_addr)) == -1) {
    printf("Error: bad connect\n");
    return -1;
  }
  return 0;
}

///@brief This function sends 1000 byte packets to the server
///
///
///
int sendFromMyClient(struct myClient* c_ptr){
  
  time_t c_now_time;
  time(&c_now_time);
  time(&c_ptr->c_start_time);

  long c_num_sent = 0;
  c_ptr->c_total_sent = 0;

  while(difftime(c_now_time, c_ptr->c_start_time) < c_ptr->c_runtime){
    //printf("Total Bytes Sent: %i\n", c_ptr->c_total_sent);
    c_num_sent = send(c_ptr->c_socket, c_ptr->data_packet, 1000, MSG_NOSIGNAL);
    time(&c_now_time);
    c_ptr->c_total_sent = c_ptr->c_total_sent + c_num_sent;
    printf("TOTAL SENT: %li\n", c_ptr->c_total_sent);
  }
  
  //Send FIN packet of all 1's and wait to recieve "ACK" from server


  send(c_ptr->c_socket, c_ptr->fin_packet, 1000, MSG_NOSIGNAL);  
  printf("FIN SENT\n");
  recv(c_ptr->c_socket, c_ptr->ack_buffer, 4, MSG_NOSIGNAL);
  if(strcmp(c_ptr->ack_buffer, "ACK") != 0){
      printf("Error: improper server ACK\n");
      return -1;
  }
  printf("ACK RECIEVED\n");
  time_t c_end_time;
  time(&c_end_time);

  //Calculate mbps and kb recieved 
  int time_elapsed = difftime(c_end_time, c_ptr->c_start_time); 
  float mbps = c_ptr->c_total_sent / time_elapsed / 100000 * 8;
  long kb_rec = c_ptr->c_total_sent / 1000;

  float mb = c_ptr->c_total_sent/ 1000000 * 8;
  printf("TIME ELAPSED: %i\n", time_elapsed);
  printf("MEGABITS: %f\n", mb);
  printf("Sent=%ld KB, Rate=%0.3f Mbps\n", kb_rec, mbps);

  return 0;
}

///@brief This function sends one 1000 byte packet to test server and client connections
///
///
///
int testSendPacketFromClient(struct myClient* c_ptr){
  int c_num_sent = 0;
  c_num_sent = send(c_ptr->c_socket, c_ptr->data_packet, 1000, MSG_NOSIGNAL);

  //Send FIN packet of all 1's and wait to recieve "ACK" from server
  c_num_sent = send(c_ptr->c_socket, c_ptr->fin_packet, 1000, MSG_NOSIGNAL);
  recv(c_ptr->c_socket, c_ptr->ack_buffer, 4, MSG_NOSIGNAL);
  if(strcmp(c_ptr->ack_buffer, "ACK") != 0){
      printf("Error: improper server ACK\n");
      return -1;
  }
  return 0;
}

///@brief This function builds the 1000 byte packet to be send to the server.
///
///
///
void buildPacket(struct myClient* c_ptr){
  for(int i = 0; i < 1000; ++i){
    c_ptr->data_packet[i] = PACKET_BYTE;
    c_ptr->fin_packet[i] = FIN_BYTE;
  }
}

///@brief This is the main clientrunning loop
///
///@param argv The command line arguments, used here to get the target port, hostname, and the time for which to run

int runMyClient(char* argv[]){
  //Create myClient struct
  struct myClient my_client;
  struct myClient* my_client_ptr = &my_client;
  my_client.c_runtime = atoi(argv[7]);

  buildPacket(my_client_ptr);
  
  if(setupMyClientSocket(my_client_ptr, argv[3], atoi(argv[5])) == -1){
    printf("Error: client setup\n");
    return -1;
  }

  //testSendPacketFromClient(my_client_ptr);
  sendFromMyClient(my_client_ptr); 
  
  return 0;
}