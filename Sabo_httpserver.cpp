//Cobi Sabo
//Networks, "HTTP Server"
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
#include <sys/stat.h>
#include <fstream>
#include <sstream>

#define MAXHOSTNAME 256

using namespace std;

class message{
    
    public:
    string text;
    time_t current;
    string type;
    
};

class Request{
    
    public:
    string method;
    string path;
    string version;
    unordered_map<string,string> headers;
    string data;
    
    void setMethod(string m){
        method = m;
    }
    
    string getMethod(){
        return method;
    }
    
    void setPath(string p){
        path = p;
    }
    
    string getPath(){
        return path;
    }
    
    void setData(string d){
        data = d;
    }
	
	void addHeader(string h1, string h2){
		headers[h1] = h2;
	}
    
    string getHeader(string h){
        return headers[h];
    }

    string toString(){
		string nice;
		nice += method + " " + path + " HTTP/" + version + "\r\nHost: localhost\r\n";
        if(method == "GET"){
			for(auto x : headers)
				nice += x.first+": "+x.second+"\r\n";
			return nice;
		}
            
        if(method == "POST"){
            int b = data.length();
            string bs = to_string(b);
            return nice+"Content-Length: "+ bs + "\r\nConnection: close\r\n\r\n" +data;
        }
    }
};

class Response{
    
    public:
    string version;
    int code;
    string message;
    unordered_map<string,string> headers;
    
    void setCode(int c){
        code = c;
    }
    
    void addHeader(string header, string value){
        headers[header] = value;
    }
    
    string getHeader(string h){
        return headers[h];
    }
    
    string toString(){
        if(code == 200){
            message = "HTTP/"+version+" "+to_string(code)+" ok\r\n";
            for(auto x : headers){
                if(x.first == "Last-Modified" || x.first == "Date")
                    message += x.first + ": " + x.second;
                else
                    message += x.first + ": " + x.second + "\r\n";
            }
            message += "\r\n";
        }
        else if(code == 400){
            message = "HTTP/"+version+" "+to_string(code)+" request malformed\n";
        }
        else if(code == 404){
            message = "HTTP/"+version+" "+to_string(code)+" not found\n";
        }
        else if(code == 500){
            message = "HTTP/"+version+" "+to_string(code)+" oops\n";
        }
        return message;
    }
};

string root = "./html";

int main(){
    
	//some definitions taken from example on Github
	struct sockaddr_in SocketInfo;
    char sysHost[MAXHOSTNAME+1];
	struct hostent *hPtr;
	int socketHandle;
    int portNumber = 8800;
    message m;
    string GorP;
    string resp;
    Request req;
    Response res;
    char * tok1;
    char* tok2;
    char* tok3;
    char* svptr1;
    char* svptr2;
    int i = 0;
    int j = 1;
    string mid;
    int getfile;
    struct stat holdInfo;

    bzero(&SocketInfo, sizeof(sockaddr_in));
    gethostname(sysHost, MAXHOSTNAME);
	
	//Retrieve system information 
	if((hPtr = gethostbyname(sysHost)) == NULL)
        {
      cerr << "System hostname misconfigured." << endl;
      exit(EXIT_FAILURE);
    }
   
   //creating socket
   if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
      close(socketHandle);
      exit(EXIT_FAILURE);
    }
   
   // Load system information into socket data structures
   //memcpy((char *)&SocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
   SocketInfo.sin_family = AF_INET;
   SocketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
   SocketInfo.sin_port = htons((u_short)portNumber);
	
   if(bind(socketHandle, (struct sockaddr *)&SocketInfo, sizeof(SocketInfo)) < 0)
   {
      close(socketHandle);
      perror("bind");
       res.setCode(500);
      exit(EXIT_FAILURE);
   }
   
   listen(socketHandle,1);
   
   while(1){ 
   int socketConnection;
   if( (socketConnection = accept(socketHandle, NULL, NULL)) < 0){
       res.setCode(500);
       exit(EXIT_FAILURE);
   }
    
   //close(socketHandle);
    
   int rc = 0;  // Actual number of bytes read by function read()
   char buf[1024];
    
   rc =  recv(socketConnection, buf, 1024, 0);
   buf[rc] = (char) NULL;
   
   //start parsing out request
   svptr1 = buf;
    
   tok1 = strtok_r(svptr1, " ", &svptr1);
   req.setMethod((string)tok1);
   if(req.method != "GET"){
      cerr << "400: Request malformed." << endl;
      res.setCode(400);
   }
   
   tok1 = strtok_r(svptr1, " ", &svptr1);
   req.setPath((string)tok1);

   tok1 = strtok_r(svptr1, "/", &svptr1);
   tok1 = strtok_r(svptr1, "\r\n", &svptr1);
   req.version = (string)tok1;
   res.version = "1.1";
   
   //parsing out the headers
   while(j == 1){
       tok1 = strtok_r(svptr1, "\r\n", &svptr1);
       if(tok1 == NULL){
           j = 0;
       }
       else{
           string mid = (string)tok1;
           int n = mid.length();
           char inter[n+1];
           strcpy(inter, mid.c_str());
           svptr2 = inter;
           tok2 = strtok_r(svptr2, ":", &svptr2);
           tok3 = strtok_r(svptr2, "\r\n", &svptr2);
           req.addHeader((string)tok2, (string)tok3);
           //cout << (string)tok1 << endl;
       }
   }
   
   //print out the request
   cout << req.toString() << endl;
   
   //get the file information
   string path = root+req.getPath();
   int l = path.length();
   char p[l+1];
   strcpy(p, path.c_str());
   getfile = stat(&p[0], &holdInfo);

   //check if the file exists first
   if(getfile == 0){
       res.setCode(200);
   }
   else
       res.setCode(404);
   
   
   //if it does exist, request is good, start building the response
   char fileData[holdInfo.st_size];
   if(res.code == 200){
       res.addHeader("Last-Modified", (string)ctime(&holdInfo.st_mtime));
       res.addHeader("Content-Length", to_string(holdInfo.st_size));
       m.current = time(0);
       char* local = ctime(&m.current);
       res.addHeader("Date", (string)local);
       res.addHeader("Server", "httpServer");
   
        
   //determine what type of content it is (jpg, html, png, css)
   int n = req.path.length();
   char pth[n+1];
   strcpy(pth, req.path.c_str());
   tok1 = strtok(pth, ".");
   tok1 = strtok(NULL, "\0");
       
   if((string)tok1 == "html")
       res.addHeader("Content-Type", "text/html");
   else if((string)tok1 == "jpg")
       res.addHeader("Content-Type", "image/jpeg");
   else if((string)tok1 == "png")
       res.addHeader("Content-Type", "image/png");
   else if((string)tok1 == "css")
       res.addHeader("Content-Type", "text/css");
   
   //start reading file
   fstream fs;
   fs.open(&p[0],ios::in | ios::binary);
   fs.read(&fileData[0],holdInfo.st_size);
   fs.close();
   }
   
   m.text = res.toString();
   strcpy(buf, &m.text[0]);
   rc = send(socketConnection, &buf[0], strlen(buf), 0);
   if(res.code == 200)
        rc = send(socketConnection, &fileData[0], holdInfo.st_size, 0);
   close(socketConnection);
   }
    
   return 0;
}