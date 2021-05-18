#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <stdbool.h>
#include<string.h>
long sum=0,count=0;
pthread_mutex_t lock;
int numOfRandomNumbers;
long c=0;
int * arr ;
int isPrime(int num){
int i;

if(num==2) return 1;

   
 if(num%2==0)
return 0;


    //if(((num*num)-1)%8!=0)return 0;

   

      for (i = 0;i<c;i++){
		if (num%arr[i] == 0&&num!=arr[i])return 0;
            
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

/*void* fuck2(void * arg)
{  struct sum_runner_struct *arg_struct =
			(struct sum_runner_struct*) arg;

   for(int i=arg_struct->start;i<arg_struct->finish;i++)
    {    
          if(isPrime(i))
           { pthread_mutex_lock(&lock);
             arr[i]=
             pthread_mutex_unlock(&lock);
                   }
    }
}*/

int fuck2(int limit)
{ long s=0;
    // 2 and 3 are known to be prime
    if (limit > 2)
        arr[s++]=2;
    if (limit > 3)
        arr[s++]=3;
  

    bool sieve[limit];
    for (int i = 0; i < limit; i++)
        sieve[i] = false;
  
    
    for (int x = 1; x * x < limit; x++) {
        for (int y = 1; y * y < limit; y++) {
              

            int n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve[n] ^= true;
  
            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
                sieve[n] ^= true;
  
            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
                sieve[n] ^= true;
        }
    }
  
    // Mark all multiples of squares as non-prime
    for (int r = 5; r * r < limit; r++) {
        if (sieve[r]) {
            for (int i = r * r; i < limit; i += r * r)
                sieve[i] = false;
        }
    }
  
    // Print primes using sieve[]
    for (int a = 5; a < limit; a+=6){
        if (sieve[a]){c++;
          arr[s++]=a;}
  if (sieve[a+2]){c++;
          arr[s++]=a+2;}}
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
int i;
	int randomPivot = atoi(argv[1]);
 numOfRandomNumbers = atoi(argv[2]);
int random = rand();
srand(randomPivot);
arr=(int*) malloc (46341*sizeof(int));


long size1 =numOfRandomNumbers/4;
long size2=(2*numOfRandomNumbers/4)-numOfRandomNumbers/4;
long size3=(3*numOfRandomNumbers/4)-(2*numOfRandomNumbers/4);
long size4=numOfRandomNumbers-(3*numOfRandomNumbers/4);
fuck2(46341);

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
