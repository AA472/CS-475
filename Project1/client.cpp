#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>       

using namespace std;

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {      
      cout<<"Usage: "<<argv[0]<< " <Port Number>\n";
      return 1;
    }
  
  int port_number = atoi(argv[1]);

  int SocketD;
  string buffer;
  
  struct hostent *serverfd;
  struct sockaddr_in server_addr = { AF_INET, htons(port_number) };
    
  //Get the Host
  serverfd = gethostbyname( "localhost" );
  
  bcopy( serverfd->h_addr_list[0], (char*)&server_addr.sin_addr, serverfd->h_length );
 
  //Create a Socket
  SocketD = socket( AF_INET, SOCK_STREAM, 0 );

  //Connect to the Server
  connect( SocketD, (struct sockaddr*)&server_addr, sizeof(server_addr));
 
  cout << "Connected to the server on port: "<< port_number<<endl;
  cout << "Enter a string to be echoed by the server: \n";

  while(1){
    
    //Receive user input
    getline(cin, buffer);
    buffer.push_back('\n');
    
    //Faciliate communication between client and server      
    send(SocketD, buffer.c_str(), buffer.length()+1, 0);
    recv(SocketD, buffer.c_str(), buffer.length()+1, 0);

    //Echo rebuffer from server	  
    cout <<"The server echoed: "<< buffer << endl;  
  }

  close(SocketD);
  
  return(0);
}
