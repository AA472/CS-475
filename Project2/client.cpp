//Abdullah Aljandali
//Networks project 2 client
//10/11/2018

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;


int main(int argc, char *argv[]){ //receive a port number
  //enter the correct amount of args
  if(argc != 2){
    cout << "Wrong number of arguments. Enter port number only." << endl;
    return 0;
  }
  // information for sending and receiving messages
  char msg[1000000];
  
  // information for building socket/connecting
  struct addrinfo hints, *res;
  int sockfd;

  // get all of your address info
  memset(&hints, 0, sizeof hints);  // Set information for hints
  hints.ai_family = AF_INET;        // IPV4
  hints.ai_socktype = SOCK_STREAM;  // Any type of socket type

  struct hostent* ipaddress = gethostbyname("localhost");
  
  // basically same as gethostbyname, keeps things simpler
  getaddrinfo(ipaddress->h_name, argv[1], &hints, &res);

  // make a socket with your info
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // connect to the server
  connect(sockfd, res->ai_addr, res->ai_addrlen);

  string user_choice = "1999";
  do{
    
  // prompt user for information 
  cout  << "Enter an integer to get a fun fact about it. Enter 0 to quit." << endl;
  
  // must be correct input
  bzero(msg, 1);
  cin >> user_choice;
  send(sockfd, user_choice.c_str(),user_choice.length(), 0);
  if(user_choice == "0")
    break;

  
  char received[10000] = {0};
  // receive the data from the server
  int rec = recv(sockfd, &received, 10000, 0);
  if(rec < 0)
    cout << "Failed to receive data from server" << endl;

  string received_string = string(received);
 
  // display the data to the user
  cout << "Fun fact: " + received_string << endl;
  
  bzero(received,10000);
  }while(user_choice != "0");
  // close the socket when you are done communicating with the server
  close(sockfd);
  
  return 0;
}
