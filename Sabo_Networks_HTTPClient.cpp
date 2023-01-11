//Cobi Sabo
//Networks, "HTTP Client"
//Some code borrowed from c++ example on socket clients
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <unordered_map>

#define MAXHOSTNAME 256


using namespace std;

class message{
    
    public:
    string text;
    time_t current;
    string type;
    
};

class request{
    
    public:
    string method;
    string path;
    string version;
    unordered_map<string,string> headers;
    string data;
    
    void setMethod(string m){
        method = m;
    }
    
    void setPath(string p){
        path = p;
    }
    
    void setData(string d){
        data = d;
    }
	
	void addHeader(string h1, string h2){
		headers[h1] = h2;
	}

    string toString(){
		string nice;
		nice += "HEAD / HTTP/1.1\r\nHost: esports.butler.edu\r\nConnection: Close\r\n\r\n";
        return nice;
        /*if(method == "GET"){
			for(auto x : headers)
				nice += x.first+": "+x.second+"\r\n";
			return nice+"Connection: close\r\n\r\n";
		}
            
        if(method == "POST"){
            int b = data.length();
            string bs = to_string(b);
            return nice+"Content-Length: "+ bs + "\r\nConnection: close\r\n\r\n" +data;
        }*/
    }
};

class response{
    
    public:
    string version;
    int code;
    string message;
    string headers[10];
    string data;
    
    string getData(){
        return data;
    }
    
    string toString(){
        return version + "\n" + headers[0] + "\n" + headers[1] + "\n" + headers[2] + "\n" + 
		headers[3] + "\n" + headers[4] + "\n" + headers[5] + "\n" + headers[6] + "\n\n"+data;
    }
};

int main(){
    
	//some definitions taken from example on Github
	struct sockaddr_in SocketInfo;
	struct hostent *hPtr;
	int socketHandle;
	const char *remoteHost = "esports.butler.edu";
    int portNumber = 80;
    message m;
    string GorP;
    string resp;
    request req;
    response res;
    char * tok;
    int i = 0;

    bzero(&SocketInfo, sizeof(sockaddr_in));
	
	//Retrieve system information 
	if((hPtr = gethostbyname(remoteHost)) == NULL)
        {
      cerr << "System DNS name resolution not configured properly." << endl;
      cerr << "Error number: " << ECONNREFUSED << endl;
      exit(EXIT_FAILURE);
    }
   
   //creating socket
   if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
      close(socketHandle);
      exit(EXIT_FAILURE);
    }
   
   // Load system information into socket data structures
   memcpy((char *)&SocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
   SocketInfo.sin_family = AF_INET;
   SocketInfo.sin_port = htons((u_short)portNumber);
	
   if(connect(socketHandle, (struct sockaddr *)&SocketInfo, sizeof(sockaddr_in)) < 0)
   {
      close(socketHandle);
      exit(EXIT_FAILURE);
   }
   
   //asking for method
   /*cout << "Would you like to GET or POST? ";
   getline(cin, GorP);
   
   //making sure it is a valid method
   while(GorP != "GET" && GorP != "POST"){
       cout << "Would you like to GET or POST? " << endl;
       getline(cin, GorP);
   }

   //setting up request 
   req.setMethod(GorP);
   req.version = "1.1";
   if(GorP == "GET"){
    req.setPath("/get");
	req.addHeader("Cobi", "Sabo");
   }
   if(GorP == "POST"){
    req.setPath("/post");
    req.setData("hello");
   }*/

   m.text = req.toString();
    
   int rc = 0;  // Actual number of bytes read by function read()

   char buf[1024];
	
   //copy message string into buffer to send over the socket
   strcpy(buf,&m.text[0]);
   rc = send(socketHandle, &buf[0], strlen(buf)+1, 0);
    
   bzero(&SocketInfo, sizeof(sockaddr_in));
   
   //rc = read(socketHandle, &buf[0], 1024);
   while((rc = read(socketHandle, &buf[0], 1024)) > 0){
       //cout << buf << endl;
   } 
   
   //strtok() is used to help tokenize a string
   tok = strtok(buf, "\n");
   res.version = (string)tok;
   while(i < 7){
       tok = strtok(NULL, "\n");
       res.headers[i++] = (string)tok;
   }
   tok = strtok(NULL, "\n");
   tok = strtok(NULL, "\0");
   res.data = (string)tok;
   
   cout << res.toString() << endl;
   
   return 0;
}