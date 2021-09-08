struct Server {
  int server_port;
  int server_socket;
  struct sockaddr_in server_addr;

  struct sockaddr_in client_addr;
  socklen_t client_addr_length;
  uint32_t client_ip;
  uint32_t client_port;
  uint32_t client_name;
}
