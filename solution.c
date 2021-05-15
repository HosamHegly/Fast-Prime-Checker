#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

long sum=0,count=0;
pthread_mutex_t lock;
int numOfRandomNumbers;


int isPrime(int num){
int i;

if(num==2||num==3) 
return 1;
   
 if(num%2==0||num%3==0)
return 0;


  //  if(((num*num)-1)%8!=0)return 0;
if((num-1)%6!=0&&((num+1)%6)!=0||((num*num)-1)%8!=0)return 0;
   

      for (i = 5;i*i<=num;i+=6){
		if (num%i == 0||num%(i+2)==0)return 0;
            
	}
	return 1;
}

void* fuck(void * arg)
{  int size=*(int*) arg;
   int random;
   for(int i=0;i<size;i++)
    {    random=rand();
          if(isPrime(random))
           { pthread_mutex_lock(&lock);
             sum+=random;
           count+=1;
             pthread_mutex_unlock(&lock);
                   }
    }
}
int main(int argc, char *argv[])
{

if(pthread_mutex_init(&lock,NULL)!=0){
           printf("mutix init failed\n"); return 0;}
	if(argc != 3) {
	    printf("Too few arguments ");
	    printf("USAGE: ./primeCalc <prime pivot> <num of random numbers>");
            exit(0);
    	}
	pthread_t tids[4];

	int randomPivot = atoi(argv[1]);
 numOfRandomNumbers = atoi(argv[2]);
int random = rand();
srand(randomPivot);
 
long size1 =numOfRandomNumbers/4;
long size2=(2*numOfRandomNumbers/4)-numOfRandomNumbers/4;
long size3=(3*numOfRandomNumbers/4)-(2*numOfRandomNumbers/4);
long size4=numOfRandomNumbers-(3*numOfRandomNumbers/4);

pthread_create(&tids[0], NULL, fuck, &size1);
pthread_create(&tids[1], NULL, fuck, &size2);
pthread_create(&tids[2], NULL, fuck, &size3);
pthread_create(&tids[3], NULL, fuck, &size4);

pthread_join(tids[0], NULL);
pthread_join(tids[1], NULL);
pthread_join(tids[2], NULL);
pthread_join(tids[3], NULL);

       
         pthread_mutex_destroy(&lock);
	//keep the out format as this!!
	printf("%ld,%ld\n",sum,count);

    	exit(0);
}
