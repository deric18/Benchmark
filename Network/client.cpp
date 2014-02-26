#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <pthread.h>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#define SERVER "192.x.x.x"
using namespace std;
void * threadit(void * );
int portNo,proto,port2,i2;

int main (int argc, char* argv[])
{
    
    bool loop = false;      
    pthread_t threads[4];
    int n,s[4] = {0,1,2,3};
    if(argc < 3)
    {
        cerr<<"Syntax : ./client  <port> <buffer_size>"<<endl;
        return 0;
    }
    port2 = atoi(argv[1]);
    
    cout<<"ENTER THE COMMUNICATION PROTOCOL TO CHOOSE FROM : "<<endl<<"1.TCP"<<endl<<"2.UDP"<<endl;
    cin>>proto;
    portNo = atoi(argv[2]);
    
   
    
   
    cout<<"ENTER THE NUMER OF THREADS TO EXECUTE"<<endl;
    cin>>n;
    for( i2=0;i2<n;i2++)
      pthread_create(&(threads[i2]), NULL, threadit,&s[i2] );
    for( i2=0;i2<n;i2++)
      pthread_join(threads[i2],NULL);
    
   
}

void * threadit(void * dums)
{
   
    double time_spent;    
    double begin,end; 
    struct sockaddr_in svrAdd;
    int checker;
    int listenFd;
    int* num1 = (int *)dums;
    int num2 = *num1;
    cout<<num2<<endl;
    int i,mem;
         
   
    //create client skt
    if(proto == 1)
    {
	    listenFd = socket(AF_INET, SOCK_STREAM, 0);
	   
	    
	    if(listenFd < 0)
	    {
		cerr << "Cannot open socket" << endl;
		return 0;
	    }
	    
	    bzero((char *) &svrAdd, sizeof(svrAdd));
	    svrAdd.sin_family = AF_INET;
	    svrAdd.sin_addr.s_addr= INADDR_ANY;
	    svrAdd.sin_port = htons(port2+num2);
	    
	    checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
	    
	    if (checker < 0)
	    {
		cerr << "Cannot connect!" << endl;
		return 0;
	    }
	    else
	    {	if(portNo == 1)
		{	
			char s[8];
			for( i=0;i<8;i++)
			s[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 byte"<<endl;
			begin =(double) clock();
			for(int j=0;j<5000;j++)
			for(int i=0;i<1024;i++)
			{
			write(listenFd, s, 8);
			read(listenFd, s, 8);
			//cout<<i;
			}
			end = (double) clock();
			time_spent = (end -begin)/CLOCKS_PER_SEC;
			cout<<"Total Time consumed for duplex transmission: "<<time_spent<<endl;
			cout<<"SPEED = "<< (1024/(time_spent+0.000000))<<"MB/SEC"<<endl;
		}
		else if(portNo == 2)
		{	
			char s1[1024];
			for( i=0;i<1024;i++)
				s1[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 kilo byte"<<endl;
			//write(listenFd,(void *)&k,1);
			begin = (double) clock();
			for(int j =0 ;j<512;j++)
			for(i=0;i<1024;i++)
			{
			write(listenFd, s1, 1024);
			read(listenFd, s1, 1024);
			//cout<<i;
			}
			end = (double) clock();
			time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
			cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
			cout<<"SPEED = "<<((1024/(time_spent)))<<"MB/SEC"<<endl;
		}
		else if(portNo == 3)
		{
			char s2[6144];
			for( i=0;i<6144;i++)
				s2[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS 1 mega byte"<<endl;
			begin = (double) clock();
			for(i=0;i<7;i++)
			for(int j=0;j<1020;j++)
			{
			write(listenFd, s2, 6144);
			read(listenFd,s2,6144);
			//cout<<i;
			}
			end = (double) clock();
			cout<<portNo<<endl;
			time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
			cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
			cout<<"SPEED = "<< (1024/(time_spent+0.00000))<<"MB/SEC"<<endl;
		}
		else
		{
			cout<<"INVALID OPTION"<<endl;
		
		}close(listenFd);
	   }
   } 
   else if(proto == 2)
   {    
	//struct sockaddr_in udp_other;
	size_t len = sizeof(svrAdd);
	listenFd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &svrAdd, sizeof(svrAdd));
  	svrAdd.sin_family = AF_INET;
  	svrAdd.sin_addr.s_addr= htonl(INADDR_ANY);
   	svrAdd.sin_port = htons(port2+num2);
	//if (inet_aton(SERVER , &svrAdd.sin_addr) == 0)            // Create datagram with server IP and port.
	//{
   	//	 cerr<<"inet_aton() failed"<<endl;
    	//	exit(1);
	//}

	if(portNo == 1)
	{	
		char s[8];
		for( i=0;i<8;i++)
		s[i] = i;
		cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 byte"<<endl;
		begin = (double) clock();
		for(int j=0;j<50000;j++)
		for(int i=0;i<1024;i++)
		{
		  sendto(listenFd,s,8,0,(struct sockaddr *)&svrAdd,len);
		  recvfrom(listenFd,s,8,0,(struct sockaddr *)&svrAdd,&len);
		//cout<<i;
		}
		end = (double) clock();
		time_spent = (end -begin)/CLOCKS_PER_SEC;
		cout<<"Total Time consumed for duplex transmission: 0sec"<<endl;
		cout<<"SPEED = "<< (1024/(time_spent+0.000000)) <<"MB/SEC"<<endl;
	}
	else if(portNo == 2)
	{	
		char s1[1024];
		for( i=0;i<1024;i++)
			s1[i] = i;
		cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 kilo byte"<<endl;
		//write(listenFd,(void *)&k,1);
		begin = (double) clock();
		for(int j =0 ;j<512;j++)
		for(i=0;i<1024;i++)
		{
			sendto(listenFd,s1,1024,0,(struct sockaddr *)&svrAdd,len);
		 	recvfrom(listenFd,s1,1024,0,(struct sockaddr *)&svrAdd,&len);
		}
		end = (double) clock();
		time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
		cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
		cout<<"SPEED = "<<((1024/(time_spent)))<<"MB/SEC"<<endl;
	}
	else if(portNo == 3)
	{
		char s2[6144];
		for( i=0;i<6144;i++)
			s2[i] = i;
		cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS 1 mega byte"<<endl;
		begin = (double) clock();
		for(i=0;i<7;i++)
		for(int j=0;j<1020;j++)
		{
			sendto(listenFd,s2,6144,0,(struct sockaddr *)&svrAdd,len);
		        recvfrom(listenFd,s2,6144,0,(struct sockaddr *)&svrAdd,&len);
		//cout<<i;
		}
		end = (double) clock();
		time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
		cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
		cout<<"SPEED = "<< (1024/(time_spent+0.00000))<<"MB/SEC"<<endl;
	}
	else
	{
		cout<<"INVALID OPTION"<<endl;
		
	}close(listenFd);
	
    }
    else
    cout<<"INVALID OPTION"<<endl;
}
