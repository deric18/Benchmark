#include<iostream>
#include<stdio.h>
#include<ctime>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;

#define BYTE 1
#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define GIGABYTE 1024*1024*1024

clock_t startTime,endTime;
double totalTimeToRead, totalTimeToWrite;
FILE *fp;
char *buffer=new char[BYTE];
void* status;

void* byteTransfer(void *){
	for(int i=0;i<BYTE;i++){
	   buffer[i]=char(i);
	}
	fp=fopen("input.txt","r+");

	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<1000000;i++)
	    fwrite(buffer,1,BYTE,fp);	
	endTime=clock();
	totalTimeToWrite=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<(double)(totalTimeToWrite/1000000)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<(1000000*BYTE)/(1024*1024*totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<1000000;i++)
	    fread(buffer,BYTE,1,fp);	
	endTime=clock();
	totalTimeToRead=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<(double)(totalTimeToWrite/1000000)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<(double)(1000000*BYTE)/(1024*1024*totalTimeToRead)<<" Mb/sec"<<endl;
	// No random access for BYTE transfer operation as we access only one byte
	//Random access	
	cout<<endl<<"**Random Access**"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<1000000;i++){
	  for(int j=0;j<BYTE;j++){
	    int r=rand()%BYTE;
	    fseek(fp,r,SEEK_SET); 	 	
	    fwrite(buffer,1,BYTE,fp);
	  }		
	}
	endTime=clock();
	totalTimeToWrite=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Write Latency :"<<(double)totalTimeToWrite/(1000000*BYTE)*1000<<" msec"<<endl;
	cout<<"Random Write Throughput:"<<(double)(1000000)/(1024*1024*totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<1000000;i++){
	  for(int j=0;j<BYTE;j++){
	    int r=rand()%BYTE;
	    fseek(fp,r,SEEK_SET);
	    fread(buffer,BYTE,1,fp);
	  }
	}	
	endTime=clock();
	totalTimeToRead=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Read Latency :"<<(double)totalTimeToWrite/(1000000*BYTE)*1000<<" msec"<<endl;
	cout<<"Random Read Throughput:"<<(1000000)/(1024*1024*totalTimeToRead)<<" Mb/sec"<<endl;
	

	
	pthread_exit(NULL);
}

void* kiloByteTransfer(void *){
	for(int i=0;i<BYTE;i++){
	   buffer[i]=char(i);
	}
	fp=fopen("input.txt","r+");
	//sequential access
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<50000;i++){
	  for(int j=0;j<KILOBYTE;j++){
	    fwrite(buffer,1,BYTE,fp);
	  }		
	}
	endTime=clock();
	totalTimeToWrite=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Seq Write Latency:"<<(double)totalTimeToWrite/(50000*KILOBYTE)*1000<<" msec"<<endl;
	cout<<"Seq Write Throughput:"<<(50000)/(1024*totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<50000;i++){
	  for(int j=0;j<KILOBYTE;j++){
	    fread(buffer,BYTE,1,fp);
	  }
	}	
	endTime=clock();
	totalTimeToRead=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Seq Read Latency :"<<(double)totalTimeToWrite/(50000*KILOBYTE)*1000<<" msec"<<endl;
	cout<<"Seq Read Throughput:"<<(50000)/(1024*totalTimeToRead)<<" Mb/sec"<<endl;
	
	//Random access	
	cout<<endl<<"**Random Access**"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<50000;i++){
	  for(int j=0;j<KILOBYTE;j++){
	    int r=rand()%KILOBYTE;
	    fseek(fp,r,SEEK_SET); 	 	
	    fwrite(buffer,1,BYTE,fp);
	  }		
	}
	endTime=clock();
	totalTimeToWrite=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Write Latency :"<<(double)totalTimeToWrite/(50000*KILOBYTE)*1000<<" msec"<<endl;
	cout<<"Random Write Throughput:"<<(double)(50000)/(1024*totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<50000;i++){
	  for(int j=0;j<KILOBYTE;j++){
	    int r=rand()%KILOBYTE;
	    fseek(fp,r,SEEK_SET);
	    fread(buffer,BYTE,1,fp);
	  }
	}	
	endTime=clock();
	totalTimeToRead=(double)(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Read Latency :"<<(double)totalTimeToWrite/(50000*KILOBYTE)*1000<<" msec"<<endl;
	cout<<"Random Read Throughput:"<<(50000)/(1024*totalTimeToRead)<<" Mb/sec"<<endl;
	
	pthread_exit(NULL);
}
// function to read and write data from disk in MEGABYTES
void* megaByteTransfer(void *){
	for(int i=0;i<BYTE;i++){
	   buffer[i]=char(i);
	}
	fp=fopen("input.txt","r+");
	//sequential access
	cout<<"Sequential Access"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<25;i++){
	  for(int j=0;j<MEGABYTE;j++){
	    fwrite(buffer,1,BYTE,fp);
	  }		
	}
	endTime=clock();
	totalTimeToWrite=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Seq Write Latency :"<<(double)totalTimeToWrite/(25*MEGABYTE)*1000<<" msec"<<endl;
	cout<<"Seq Write Throughput:"<<(25)/(totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<25;i++){
	  for(int j=0;j<MEGABYTE;j++){
	    fread(buffer,BYTE,1,fp);
	  }
	}	
	endTime=clock();
	totalTimeToRead=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Seq Read Latency :"<<(double)totalTimeToWrite/(25*MEGABYTE)*1000<<" msec"<<endl;
	cout<<"Seq Read Throughput:"<<25/(totalTimeToRead)<<" Mb/sec"<<endl;
	
	//Random access	
	cout<<"**Random Access**"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	for(int i=0;i<25;i++){
	  for(int j=0;j<MEGABYTE;j++){
	    int r=rand()%MEGABYTE;
	    fseek(fp,r,SEEK_SET); 	 	
	    fwrite(buffer,1,BYTE,fp);
	  }		
	}
	endTime=clock();
	totalTimeToWrite=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Write Latency :"<<totalTimeToWrite/(25*MEGABYTE)*1000<<" msec"<<endl;
	cout<<"Random Write Throughput:"<<(25)/(totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	for(int i=0;i<25;i++){
	  for(int j=0;j<MEGABYTE;j++){
	    int r=rand()%MEGABYTE;
	    fseek(fp,r,SEEK_SET);
	    fread(buffer,BYTE,1,fp);
	  }
	}	
	endTime=clock();
	totalTimeToRead=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Random Read Latency :"<<totalTimeToRead/(25*MEGABYTE)*1000<<" msec"<<endl;
	cout<<"Random Read Throughput:"<<(25)/(totalTimeToRead)<<" Mb/sec"<<endl;
	
	pthread_exit(NULL);
}
// function to read and write data from disk in GIGABYTES
void* gigaByteTransfer(void *){
	for(int i=0;i<BYTE;i++){
	   buffer[i]=char(i);
	}
	fp=fopen("input.txt","r+");
	//sequential access
	cout<<"Sequential Operation"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	//for(int i=0;i<1000;i++){
	  for(int j=0;j<GIGABYTE;j++){
	    fwrite(buffer,1,BYTE,fp);
	  }		
	//}
	endTime=clock();
	totalTimeToWrite=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<totalTimeToWrite/(GIGABYTE)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<1024/(totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	//for(int i=0;i<1000;i++){
	  for(int j=0;j<GIGABYTE;j++){
	    fread(buffer,BYTE,1,fp);
	  }
	//}	
	endTime=clock();
	totalTimeToRead=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<totalTimeToRead/(GIGABYTE)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<1024/(totalTimeToRead)<<" Mb/sec"<<endl;
	
	//Random access	
	cout<<endl<<"**Random Access**"<<endl;
	// Write Operation
	cout<<"Write Operation"<<endl;
	startTime=clock();
	//for(int i=0;i<1000;i++){
	  for(int j=0;j<GIGABYTE;j++){
	    int r=rand()%GIGABYTE;
	    fseek(fp,r,SEEK_SET); 	 	
	    fwrite(buffer,1,BYTE,fp);
	  }		
	//}
	endTime=clock();
	totalTimeToWrite=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<totalTimeToWrite/(GIGABYTE)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<1024/(totalTimeToWrite)<<" Mb/sec"<<endl;
	// Read Operation
	cout<<"Read Operation"<<endl;
	startTime=clock();
	//for(int i=0;i<1000;i++){
	  for(int j=0;j<GIGABYTE;j++){
	    int r=rand()%GIGABYTE;
	    fseek(fp,r,SEEK_SET);
	    fread(buffer,BYTE,1,fp);
	  }
	//}	
	endTime=clock();
	totalTimeToRead=(endTime-startTime)/CLOCKS_PER_SEC;
	cout<<"Latency :"<<totalTimeToRead/(GIGABYTE)*1000<<" msec"<<endl;
	cout<<"Throughput:"<<1024/(totalTimeToRead)<<" Mb/sec"<<endl;
	
	pthread_exit(NULL);
}
main()
{
	pthread_t *thread = new pthread_t[10];//create threads
	//set the attribute to JOINABLE
	pthread_attr_t attribute;
	pthread_attr_init (&attribute);
	pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);		
	int ch,r,r1;
	char ch1;
	//menu for the user to enter his desired choice
	while(1){
	cout<<"\n\n1. Single thread Byte Transfer\n2. Single thread KiloByte Transfer\n3. Single thread MegaByte Transfer\n4. Single thread GigaByte Transfer\n5. Two threads Byte Transfer\n6. Two threads KiloByte Transfer\n7. Two threads MegaByte Transfer\n8. Two threads GigaByte Transfer";

	cout<<"\nSelect your choice : ";
	cin>>ch;
		
	switch(ch)
	{
	
		case 1 : cout<<"\n---Byte Transfer operation on Single thread---"<<endl;
			 r = pthread_create(&thread[0],&attribute,byteTransfer,NULL);
			 pthread_join(thread[0], &status);
			 break;

		case 2 : cout<<"\n---KiloByte Transfer operation on Single thread ---"<<endl;
			 r = pthread_create(&thread[0],&attribute,kiloByteTransfer,NULL);	 
			 pthread_join(thread[0], &status);
			 break;

		case 3 : cout<<"\n---MegaByte Transfer operation on Single thread---"<<endl;
			 r = pthread_create(&thread[0],&attribute,megaByteTransfer,NULL);	 
			 pthread_join(thread[0], &status);
			 break;

		case 4 : cout<<"\n---GigaByte Transfer operation on Single thread---"<<endl;
			 r = pthread_create(&thread[0],&attribute,gigaByteTransfer,NULL);	 
			 pthread_join(thread[0], &status);
			 break;

		case 5 : cout<<"\n---Byte Transfer operation on Two threads ---"<<endl;
			 r = pthread_create(&thread[0],&attribute,byteTransfer,NULL);
			 if(r!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 
			 
			 r1 = pthread_create(&thread[1],&attribute,byteTransfer,NULL);
			 if(r1!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 pthread_join(thread[0], &status);
			 pthread_join(thread[1], &status);
			 break;

		case 6 : cout<<"\n---KiloByte Transfer operation on Two threads---"<<endl;
			 r = pthread_create(&thread[0],&attribute,kiloByteTransfer,NULL);
			 if(r!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 
			 r1 = pthread_create(&thread[1],&attribute,kiloByteTransfer,NULL);
			 if(r1!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 pthread_join(thread[0], &status);
			 pthread_join(thread[1], &status);
			 break;

		case 7 : cout<<"\n---MegaByte Transfer operation on Two threads---"<<endl;
			 r = pthread_create(&thread[0],&attribute,megaByteTransfer,NULL);
			 if(r!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			
			 r1 = pthread_create(&thread[1],&attribute,megaByteTransfer,NULL);
			 if(r1!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 pthread_join(thread[0], &status);
			 pthread_join(thread[1], &status);
			 break;

		case 8 : cout<<"\n---GigaByte Transfer operation on Two threads---"<<endl;
			 r = pthread_create(&thread[0],&attribute,gigaByteTransfer,NULL);
			 if(r!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 r1 = pthread_create(&thread[1],&attribute,gigaByteTransfer,NULL);
			 if(r1!=0)
			 {
				cout<<"\n Error in creating thread "<<r<<endl;
				exit(-1);	 
			 }
			 pthread_join(thread[0], &status);
			 pthread_join(thread[1], &status);
			 break;

		default : cout<<"\nPLEASE ENTER A VALID INPUT..!!";
	}

	cout<<"\n\nDo you wish to continue...??? (y/n)";
	cin>>ch1;

	if(ch1=='y')
		continue;

	else
		exit(0);
	}
	free(buffer);
}

