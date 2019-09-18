//Abdullah Aljandali
//Networks project 2
//10/11/2018

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


using namespace std;

int port = 61500;

int main(int argc, char *argv[])
{

  string user_input;
  int SocketD;
   char clientResponse[10];
  SocketD = socket(AF_INET, SOCK_STREAM, 0);
  cout << "My Socket Discriptor is: " << SocketD << endl;

  
  struct sockaddr_in self;
  self.sin_family = AF_INET;
  self.sin_port = htons(port);            
  self.sin_addr.s_addr = INADDR_ANY;      
  //connect to server
  bind(SocketD, (struct sockaddr*)&self, sizeof(self));
  cout << "Server is Listening on port: " << port << endl;
  listen(SocketD, 20);
  struct sockaddr_in client_addr;
  int addrlen = sizeof(client_addr);
  int clientfd = accept(SocketD, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
  cout << "connected with client" << endl;

   do{
     // connect to api
  struct hostent *host;
  struct in_addr **addr_list;
  string name = "numbersapi.com";
  host = gethostbyname(name.c_str());
  addr_list = (struct in_addr **)host->h_addr_list;
  string IP  = inet_ntoa(*addr_list[0]);
  struct sockaddr_in serv_addr;
  int sock = 0, valread;
  recv(clientfd, &clientResponse, 10, 0);
  user_input = string(clientResponse);
  if(user_input=="0"){
    close(sock);
     break;
  }
  bzero(clientResponse, 1);
  string msg  = "GET http://numbersapi.com/"+user_input+"/year\n";
  char buffer[10000] = {0}; 
  sock = socket(AF_INET, SOCK_STREAM, 0);
  cout<<"socket created."<<endl;
  memset(&serv_addr,'0',sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(80);

  inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr);
  if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    cout<<"error"<<endl;
  else
    cout<<"connected made to website."<<endl;

  send(sock, msg.c_str(), msg.length(), 0);
  cout<<"sent: "<<msg <<endl;
  valread = recv(sock,buffer,10000,0);
  cout<<"recieved: "<<buffer<<endl;

  send(clientfd, buffer , 10000, 0);
  bzero(buffer, 10000);
 
  close(sock);
   }while(1);
  close(SocketD);
  return 0;

}
