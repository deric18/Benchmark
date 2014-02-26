#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <string>
#include <pthread.h>

using namespace std;

void *task1(void *);
//static int connFd;
int buffer_size,proto,port,i1;

int main(int argc, char* argv[])
{
   
    pthread_t threads[4];
    int n,s[4] = {0,1,2,3};
    
    
    if (argc < 2)
    {
        cerr << "Syntax : ./server <buffer size> <port> <no_of_threads>" << endl;
        return 0;
    }
    
    buffer_size = atoi(argv[1]);
    port = atoi(argv[2]);
    n = atoi(argv[3]);
   
    cout<<"ENTER THE COMMUNICATION PROTOCOL TO CHOOSE FROM : "<<endl<<"1.TCP"<<endl<<"2.UDP"<<endl;
    cin>>proto;
   
    
    //len = sizeof(clntAdd);
    
    cout << "Listening" << endl;

    for(i1=0;i1<n;i1++)
    { 
	pthread_create(&(threads[i1]),NULL,task1,&s[i1]);
    }
    for(i1=0;i1<n;i1++)
    {
	pthread_join(threads[i1],NULL);
    }
    
    exit(1);
    
}

void *task1 (void *num)
{
 	int connFd,newconnFd;
	double begin,end,time_spent;
	struct sockaddr_in svrAdd;
 	int* num1 = (int *)num ;
	int num2 = *num1,i;
	cout<<num2<<endl;
	

 //create client skt
   	 if(proto == 1)
   	 {
		connFd = socket(AF_INET, SOCK_STREAM, 0);
   		 //create socket
    		// connFd = socket(AF_INET, SOCK_STREAM, 0);
    
   		 if(connFd < 0)
   		 {
   	  	   cerr << "Cannot open socket" << endl;
    	  	   return 0;
	       	 }
		 
    //bzero((char*) &svrAdd, sizeof(svrAdd));
    
   		 svrAdd.sin_family = AF_INET;
    		 svrAdd.sin_addr.s_addr = INADDR_ANY;
    	 	 svrAdd.sin_port = htons(port+num2);
    
    //bind socket
   		 if(bind(connFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    		 {
	       		 cerr << "Cannot bind" << endl;
	       		 return 0;
    		 }
    	
   	 	listen(connFd, 2);
		 
         	cout << "Thread No: " << pthread_self() << endl;
    
    	 	newconnFd = accept(connFd, (struct sockaddr *)0,0);

        	if (newconnFd < 0)
       		 {
         		   cerr << "Cannot accept connection" << connFd<< endl;
          		  return 0;
      		 }
        	else
        	{
            		cout << "Connection successful" << endl;
	    		cout << "New Connection Established "<< endl;
		
			if(buffer_size == 1)
			{	
				char s[8];
				for(int i=0;i<8;i++)
				s[i] = i;
				cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 byte"<<endl;
				for(int j=0;j<5000;j++)
				for(int i=0;i<1024;i++)
				{
					read(newconnFd, s, 8);
					write(newconnFd, s, 8);
				}
				cout<<"Total Time consumed for duplex transmission: "<<time_spent<<"sec"<<endl;
				cout<<"SPEED = "<< (1024/(time_spent+0.000000)) <<"MB/SEC"<<endl;
			}
			else if(buffer_size == 2)
			{	
				char s1[1024];
				for(int i=0;i<1024;i++)
				s1[i] = i;
				cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 kilo byte"<<endl;
			//write(connFd,(void *)&k,1);
				begin = (double) clock();
				for(int j =0 ;j<512;j++)
				for(int i=0;i<1024;i++)
				{
					read(newconnFd,s1,1024);
					write(newconnFd, s1, 1024);
		
			//cout<<i;
				}
				end = (double) clock();
				time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
				cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
				cout<<"SPEED = "<<((1024/(time_spent+0.000000)))<<"MB/SEC"<<endl;
			}
			else if(buffer_size == 3)
			{
				char s2[6144];
				for(int i=0;i<6144;i++)
					s2[i] = i;
				cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS 1 mega byte"<<endl;
				begin = (double) clock();
				for(int i=0;i<7;i++)
				for(int j=0;j<1020;j++)
				{
					read(newconnFd, s2,6144);
					write(newconnFd, s2,6144);
				}
				end = (double) clock();
				cout<<buffer_size<<endl;
				time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
				cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
				cout<<"SPEED = "<< (1024/(time_spent+0.0000000))<<"MB/SEC"<<endl;
			}
			else
			{
				cout<<"INVALID OPTION"<<endl;
			}
		}
	    		cout << "\nClosing thread and conn" << endl;
   			close(connFd);
	 }
   	 else if(proto == 2)
   	 {
		struct sockaddr_in udp_other;
		size_t len = sizeof(udp_other);
		connFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		bzero((char *) &svrAdd, sizeof(svrAdd));
  		svrAdd.sin_family = AF_INET;
  		svrAdd.sin_addr.s_addr= htonl(INADDR_ANY);
   		svrAdd.sin_port = htons(port+num2);
		if(bind(connFd,(struct sockaddr *) &svrAdd,sizeof(svrAdd))<0)
		{
			cerr<<"bind error"<<endl;
			exit(1);	
		}
		if(buffer_size == 1)
		{	
			char s[8];
			for( i=0;i<8;i++)
			s[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 byte"<<endl;
			begin = (double) clock();
			for(int j=0;j<50000;j++)
			for(int i=0;i<1024;i++)
			{
				recvfrom(connFd,s,8,0,(struct sockaddr *)&svrAdd,&len);
		  		sendto(connFd,s,8,0,(struct sockaddr *)&svrAdd,len);
		 	 	
			}
			end = (double) clock();
			time_spent = (end -begin)/CLOCKS_PER_SEC;
			cout<<"Total Time consumed for duplex transmission: 0sec"<<endl;
			cout<<"SPEED = "<< (1024/(time_spent+0.000000)) <<"MB/SEC"<<endl;
			}	
		else if(buffer_size == 2)
		{	
			char s1[1024];
			for( i=0;i<1024;i++)
				s1[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS"<<endl<<"1 kilo byte"<<endl;
			//write(connFd,(void *)&k,1);
			begin = (double) clock();
			for(int j =0 ;j<512;j++)
			for(i=0;i<1024;i++)
			{
				recvfrom(connFd,s1,1024,0,(struct sockaddr *)&svrAdd,&len);
				sendto(connFd,s1,1024,0,(struct sockaddr *)&svrAdd,len);
			 	
			}
			end = (double) clock();
			time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
			cout<<"Total Time consumed for duplex transmission:"<<time_spent<<endl;
			cout<<"SPEED = "<<((1024/(time_spent)))<<"MB/SEC"<<endl;
		}
		else if(buffer_size == 3)
		{
			char s2[6144];
			for( i=0;i<6144;i++)
				s2[i] = i;
			cout<<"SELECTED MEMORY RANGE FOR DUPLEX TRANSMISSIONS 1 mega byte"<<endl;
			begin = (double) clock();
			for(i=0;i<7;i++)
			for(int j=0;j<1020;j++)
			{
				recvfrom(connFd,s2,6144,0,(struct sockaddr *)&udp_other,&len);
				sendto(connFd,s2,6144,0,(struct sockaddr *)&udp_other,len);
				
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
		
		}close(connFd);
	
	    }
	    else
	    cout<<"INVALID OPTION"<<endl;
}
