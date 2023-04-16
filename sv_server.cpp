#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

int main()
{

// Tao socket
int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (listener != -1)
printf("Socket created: %d\n", listener);
else {
printf("Failed to create socket.\n");
exit(1);
}
//Nhap tu ban phim
char fileghi[20];
int portnum;
printf ("Nhap so cong: \n");
cin >> portnum;
printf ("Nhap ten file log: \n");
cin >> fileghi;
// Khai bao cau truc dia chi server
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(portnum);

// Gan dia chi voi socket
if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
{
printf("bind() failed.\n");
exit(1);
}
if (listen(listener, 5))
{
printf("listen() failed.\n");
exit(1);
}
printf("Waiting for a new client ...\n");
// Chap nhan ket noi
int client = accept(listener, NULL, NULL);
if (client == -1)
{
printf("accept() failed.\n");
exit(1);
}
printf("New client connected: %d\n", client);
// Nhan du lieu tu client
char buf[2000];
int ret = recv(client,buf, sizeof(buf), 0);
if (ret <= 0)
{
printf("recv() failed.\n");
exit(1);
}
else {

    ofstream foutput; 
 ifstream finput;
 finput.open (fileghi);
 foutput.open (fileghi,ios::app); 
 
 if(finput.is_open())
   foutput<<buf<<"\n"; 
  
 
 
 finput.close();
 foutput.close();
}
// Gui du lieu sang client
char s[60] = "Da nhan va ghi file!";
send(client, s, strlen(s), 0);
// Dong ket noi
close(client);
close(listener);
return 0;
}