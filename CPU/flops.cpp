#include<iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<pthread.h>
#include<unistd.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/stat.h>
//#include <boost/thread/thread.hpp>
//#include <boost/array.hpp>
//#include <boost/asio.hpp>
using namespace std;
pthread_t threads[4];
const int N = 100;
//message[0] = "thread 1";
//message[1] = "thread 2";
//void * computeflops(void *);
//float * compose_matrix(void);
float A[N][N],B[N][N],C[N][N];
void compose_float(float A[N][N])
{
int i,j;
for(i=0;i<N;++i)
  {
    for(j=0;j<N;++j)
    {
      A[i][j] = (float)rand()/100.0;
    }
  }
}
void * computeflops(void * param)
{
float number;
int i;




for(i = 0;i<1000;i++)
{
//number++;
 for(int i=0;i<N;++i)
  {
    for(int j=0;j<N;++j)
    {
      C[i][j] = 0;
      for(int k=0;k<N;++k)
      {
        C[i][j]+=A[i][k]*B[k][j];
      }
    }
  }
}
return NULL;
}


int main()
{
int i = 0 ,err[4],n;
double time_spent=0;
long flops;
double begin,end;
cout<<"ENTER NUMBER OF THREADS YOU WANT"<<endl;
cin>>n;
compose_float(A);
compose_float(B);
begin =(double) clock(); 
for(i=0;i<n;i++)
{
err[i] = pthread_create(&(threads[i]), NULL, computeflops, NULL);
if(err[i]!=0)
cout<<"could not create thread"<<endl;
else
cout<<"thread created succesfully"<<endl;
pthread_join( threads[i], NULL);
}
end=(double) clock();
time_spent = (double) (end-begin)/CLOCKS_PER_SEC;
cout<<"TIME SPENT:"<<time_spent<<endl;
cout<<"COMPUTING FLOPS..."<<endl;
//cout<<"CLOCK PER SEC:%ld\n",CLOCKS_PER_SEC);
flops = (1000000000/time_spent)*n;
cout<<"FLOPS :"<<flops<<endl;
return 0;
}

