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
  //Add socket option to allow address to be used again
  int ok = 1;  
  if(setsockopt(s_ptr->s_socket, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok)) == -1){
    printf("Error: bad setsockopt\n");
    return -1;
  }
  
  //Set values for sockaddr_in struct
  s_ptr->s_addr_len = (socklen_t)sizeof(s_ptr->s_addr);
  memset(&s_ptr->s_addr, 0, s_ptr->s_addr_len);
  s_ptr->s_addr.sin_family = AF_INET;
  s_ptr->s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_ptr->s_addr.sin_port = htons(s_ptr->s_port);

  //Bind socket to address
  if(bind(s_ptr->s_socket, (const struct sockaddr*) &s_ptr->s_addr, s_ptr->s_addr_len) == -1){
    printf("Error: bad bind\n");
    return -1;
  }

  //Set socket to listen
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
    s_ptr->c_addr_len = (socklen_t)sizeof(s_ptr->c_addr);
    
    //Wait for a client to make a connection to the server, accept that connection
    s_ptr->connfd = accept(s_ptr->s_socket, (struct sockaddr*)&s_ptr->c_addr, (unsigned int*)&s_ptr->c_addr_len);
    /* 
    s_ptr-> c_ip = 0;
    s_ptr-> c_port = 0;
    
    //Get format client IPv4 client address
    s_ptr->c_ip = ntohl(s_ptr->c_addr.sin_addr.s_addr);
    s_ptr->c_port = ntohs(s_ptr->c_addr.sin_port);
    sprintf(s_ptr->c_name, "%d.%d.%d.%d:%d",
    	    s_ptr->c_ip >> 24,
	    (s_ptr->c_ip & 0x00ff0000) >> 16,
	    (s_ptr->c_ip & 0x0000ff00) >> 8,
	    (s_ptr->c_ip & 0x000000ff),
	    s_ptr->c_port);
    printf("%s connected!\n", s_ptr->c_name);
    if(s_ptr->connfd == -1){
      printf("Error: bad accept\n");
      return -1;
    }
    */

    //Recieve messages from client connection and place into butter
    //num_recvd is the number of bytes recieved
    //

    //Begin timer after accept and error checking
    //Accept data as quickly as possible
    //Count number of bytes recieved and number of 1000 byte packets recieved


    char buffer[1000];
    while(1){


      s_ptr->s_num_recvd = recv(s_ptr->connfd, s_ptr->s_buffer, 1000, MSG_NOSIGNAL);
      if(s_ptr->s_num_recvd == 0){
        break;
      }
      else if(s_ptr->s_num_recvd == -1){
        printf("bad recv");
	break;
      }
      printf("[MSG_SIZE=%li BYTES]%s\n", s_ptr->s_num_recvd, s_ptr->s_buffer);

      //Send accepted message to the client
      char msg[11] = "Accepted\n";
      int num_sent = send(s_ptr->connfd, msg, 12, MSG_NOSIGNAL);

    }
    printf("%s disconnected!\n", s_ptr->c_name);
    close(s_ptr->connfd);

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
  acceptOnMyServer(my_server_ptr); 
}
