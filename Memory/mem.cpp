//code by Deric Roshan Pinto - A20300680
//program to find the throughput of memory in terms of read and write operation, sequential and random access, 1 and 2 threads
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
using namespace std;
void* SequentialReadOneByteBlock(void *);
void* SequentialReadOneByteBlock1(void *);

void* SequentialReadOneKBBlock(void *);
void* SequentialReadOneKBBlock1(void *);

void* SequentialReadOneMBBlock(void *);
void* SequentialReadOneMBBlock1(void *);

void* RandomReadOneByteBlock(void *);
void* RandomReadOneKBBlock(void *);
void* RandomReadOneMBBlock(void *);

int main()
{
	int choice;
	pthread_t thread1,thread2;
	clock_t startTime,endTime;
	for(;;)
	{
		cout<<"1.Sequential-1 thread 2.Sequential-2 threads 3.Random-1 thread 4.Random-2threads 5.Exit"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		switch(choice)
		{
			//Sequential access with varying block sizes and 1 thread.
			case 1: startTime=clock();
				pthread_create(&thread1,NULL,SequentialReadOneByteBlock,NULL);
				pthread_join(thread1,NULL);
				endTime=clock();
				cout<<"The time for 1B block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Latency is %lf "<<(((double)(endTime-startTime)/CLOCKS_PER_SEC)/(5ul*1024ul*1024ul*1024ul))*1000ul<<endl;
				cout<<"ms"<<endl;
				cout<<"Throughput for 1B block size in sequential read for 1 thread is "<<(400)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;

				startTime=clock();
                                pthread_create(&thread1,NULL,SequentialReadOneKBBlock,NULL);
                                pthread_join(thread1,NULL);
                                endTime=clock();
                                cout<<"The time for 1KB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1KB block size in sequential read for 1 thread is  "<<(16000)/((double)(endTime-startTime)/CLOCKS_PER_SEC);
				cout<<"MB/sec"<<endl;

				startTime=clock();
                                pthread_create(&thread1,NULL,SequentialReadOneMBBlock,NULL);
                                pthread_join(thread1,NULL);
                                endTime=clock();
                                cout<<"The time for 1MB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				
				cout<<"Throughput for 1MB block size in sequential read for 1 thread is  "<<(16384)/((double)(endTime-startTime)/CLOCKS_PER_SEC);
                                cout<<"MB/sec"<<endl;

				break;
			//Sequential access with varying block sizes and 2 threads.
			case 2: startTime=clock();
                                pthread_create(&thread1,NULL,SequentialReadOneByteBlock,NULL);
				pthread_create(&thread2,NULL,SequentialReadOneByteBlock,NULL);
                                pthread_join(thread1,NULL);
				pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1B block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
                                cout<<"Throughput for 1B block size in sequential read for 2 threads is  "<<(2*400)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;

				startTime=clock();
                                pthread_create(&thread1,NULL,SequentialReadOneKBBlock,NULL);
				pthread_create(&thread2,NULL,SequentialReadOneKBBlock,NULL);
                                pthread_join(thread1,NULL);
				pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1KB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1KB block size in sequential read for 2 threads is  "<<(2*16000)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec\n"<<endl;

                                startTime=clock();
                                pthread_create(&thread1,NULL,SequentialReadOneMBBlock,NULL);
				pthread_create(&thread2,NULL,SequentialReadOneMBBlock,NULL);
                                pthread_join(thread1,NULL);
				pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1MB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				
				cout<<"Throughput for 1MB block size in sequential read for 1 thread is  "<<(2*16384)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec\n"<<endl;

                                break;
			//Random access with varying block sizes and 1 thread.
			case 3: startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneByteBlock,NULL);
                                pthread_join(thread1,NULL);
                                endTime=clock();
                                cout<<"The time for 1B block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Latency is %lf "<<(((double)(endTime-startTime)/CLOCKS_PER_SEC)/(20ul*1024ul*1024ul))<<endl;
				cout<<"ms\n"<<endl;
				cout<<"Throughput for 1B block size in random read for 1 thread is  "<<(1*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec\n"<<endl;
                                startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneKBBlock,NULL);
                                pthread_join(thread1,NULL);
                                endTime=clock();
                                cout<<"The time for 1KB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1KB block size in random read for 1 thread is  "<<(256*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;
                                startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneMBBlock,NULL);
                                pthread_join(thread1,NULL);
                                endTime=clock();
                                cout<<"The time for 1MB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1MB block size in random read for 1 thread is  "<<(256*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;
                                break;
			//Random access with varying block sizes and 2 threads
			case 4: startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneByteBlock,NULL);
                                pthread_create(&thread2,NULL,RandomReadOneByteBlock,NULL);
                                pthread_join(thread1,NULL);
                                pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1B block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1B block size in random read for 2 threads is  "<<(2*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec\n"<<endl;
                                startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneKBBlock,NULL);
                                pthread_create(&thread2,NULL,RandomReadOneKBBlock,NULL);
                                pthread_join(thread1,NULL);
                                pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1KB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1KB block size in random read for 2 threads is  "<<(2*256*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;
                                startTime=clock();
                                pthread_create(&thread1,NULL,RandomReadOneMBBlock,NULL);
                                pthread_create(&thread2,NULL,RandomReadOneMBBlock,NULL);
                                pthread_join(thread1,NULL);
                                pthread_join(thread2,NULL);
                                endTime=clock();
                                cout<<"The time for 1MB block size is "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
				cout<<"Throughput for 1MB block size in random read for 2 threads is  "<<(2*256*20)/((double)(endTime-startTime)/CLOCKS_PER_SEC)<<endl;
                                cout<<"MB/sec"<<endl;
                                break;

			case 5: exit(0);
		}
	}
}


void* SequentialReadOneByteBlock(void* param)
{
	long long i;
        int j;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(1048576);
        destinationString = (char *)malloc(1048576);
        temp=sourceString;
        for(i=0;i<1048576;i++)
        {
                *temp='a';
                temp++;
        }
        temp=sourceString;
        for(j=0;j<400;j++)
        {
                for(i=0;i<1048576;i++)
                {
                        memcpy(destinationString+(i),sourceString+(i),1);
                }
	}
	free(sourceString);free(destinationString);

}

void* SequentialReadOneByteBlock1(void* param)
{
        long long i;
        int j;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(20971520);
        destinationString = (char *)malloc(20971520);
        temp=sourceString;
        for(i=0;i<20971520;i++)
        {
                *temp='a';
                temp++;
        }
        temp=sourceString;
        for(j=0;j<256;j++)
        {
                for(i=0;i<20971520;i++)
                {
                        memcpy(destinationString+(i),sourceString+(i),1);
                }
        }free(sourceString);free(destinationString);

}


void* SequentialReadOneKBBlock(void* param)
{
	long long i;
        int j;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(1048576*200);
        destinationString = (char *)malloc(1048576*200);
	temp=sourceString;
        for(i=0;i<1048576*200;i++)
        {
                *temp='a';
                temp++;
        }
        
        for(j=0;j<80;j++)
        {
                for(i=0;i<1024*200;i++)
                {
                        memcpy(destinationString+(i*1024),sourceString+(i*1024),1024);
                }
        }free(sourceString);free(destinationString);
}


void* SequentialReadOneKBBlock1(void* param)
{
        long long i;
        int j;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(1048576*20);
        destinationString = (char *)malloc(1048576*20);
        temp=sourceString;
        for(i=0;i<1048576*20;i++)
        {
                *temp='a';
                temp++;
        }
        temp=sourceString;
        for(j=0;j<20;j++)
        {
                for(i=0;i<1024;i++)
                {
                        memcpy(destinationString+(i*1024),sourceString+(i*1024),1024);
                }
        }free(sourceString);free(destinationString);
}

void* SequentialReadOneMBBlock(void* param)
{
	long long i;
        int j;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(20971520);
        destinationString = (char *)malloc(20971520);
        temp=sourceString;
	for(i=0;i<20971520;i++)
        {
                *temp='a';
                temp++;
        }

	for(j=0;j<8192;j++)
        {
                for(i=0;i<2;i++)
                {
                        memcpy(destinationString+(i*1024*1024),sourceString+(i*1024*1024),1048576);
                }
        }free(sourceString);free(destinationString);
}


void* SequentialReadOneMBBlock1(void* param)
{
        long long i;
        int j;
        char *sourceString1, *destinationString1, *temp1;
        sourceString1 = (char *)malloc(20971520);
        destinationString1 = (char *)malloc(20971520);
        temp1=sourceString1;
        for(i=0;i<20971520;i++)
        {
                *temp1='a';
                temp1++;
        }

        for(j=0;j<256;j++)
        {
                for(i=0;i<20;i++)
                {
                        memcpy(destinationString1+(i*1024*1024),sourceString1+(i*1024*1024),1048576);
                }
        }
	free(sourceString1);
	free(destinationString1);
}

void* RandomReadOneByteBlock(void* param)
{
	long long i,j,k;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(1048576);
        destinationString = (char *)malloc(1048576);
        temp=sourceString;
        for(i=0;i<1048576;i++)
        {
                *temp='a';
                temp++;
        }
        temp=sourceString;
        for(j=0;j<20;j++)
	{
		for(i=0;i<1048576;i++)
		{
			k=rand()%1048576;
			memcpy(destinationString+i,sourceString+k,1);
		}
	}free(sourceString);free(destinationString);
}
void* RandomReadOneKBBlock(void *param)
{
	long long i,j,k;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(20971520);
        destinationString = (char *)malloc(20971520);
        temp=sourceString;
        for(i=0;i<20971520;i++)
        {
                *temp='a';
                temp++;
        }

	for(j=0;j<256;j++)
        {
                for(i=0;i<20480;i++)
                {
			k=rand()%20479;
                        memcpy(destinationString+(i*1024),sourceString+(k*1024),1024);
                }
        }free(sourceString);free(destinationString);
}

void* RandomReadOneMBBlock(void *param)
{
	long long i,j,k;
        char *sourceString, *destinationString, *temp;
        sourceString = (char *)malloc(20971520);
        destinationString = (char *)malloc(20971520);
        temp=sourceString;
        for(i=0;i<20971520;i++)
        {
                *temp='a';
                temp++;
        }

        for(j=0;j<256;j++)
        {
                for(i=0;i<20;i++)
                {
                        k=rand()%19;
			memcpy(destinationString+(i*1048576),sourceString+(k*1048576),1048576);
                }
        }free(sourceString);free(destinationString);
}

int random_in_range (unsigned int min, unsigned int max)
{
  int base_random = rand(); /* in [0, RAND_MAX] */
  if (RAND_MAX == base_random) return random_in_range(min, max);
  /* now guaranteed to be in [0, RAND_MAX) */
  int range       = max - min,
      remainder   = RAND_MAX % range,
      bucket      = RAND_MAX / range;
  /* There are range buckets, plus one smaller interval
     within remainder of RAND_MAX */
  if (base_random < RAND_MAX - remainder) {
    return min + base_random/bucket;
  } else {
    return random_in_range (min, max);
  }
}

