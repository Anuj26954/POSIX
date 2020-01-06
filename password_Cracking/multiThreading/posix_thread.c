#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <ctype.h>
#include <malloc.h>
#include <errno.h>
#include <sys/stat.h>






int n_passwords = 4;





  char *encrypted_passwords[] = {


"$6$KB$0G24VuNaA9ApVG4z8LkI/OOr9a54nBfzgQjbebhqBZxMHNg0HiYYf1Lx/HcGg6q1nnOSArPtZYbGy7yc5V.wP/",

"$6$KB$Z5p6Fe7quS8nMyDnY/vxQhaR2W5Hb/F1OA9rHUtxJyFL078L3sY5yVUHzhCKE/u7gyoS26MlzroxosQits6eH/",

"$6$KB$VRDSVBeH0sRCUnYuN3VWcdmc.yfr4tlG6RbOyp1mq8.o/h28YhvCjaLamljxy6SEgXvcWapB9uiKFAhSZGTV8.",

"$6$KB$k9Tf1JT7BUYVsUsAtFzQp7inKLvRYa4e40ewNk3oK4ljTUsMig6cukiruh2/dGmteERh4qAgxE5kKeoL51sOU."
};




void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void multi_thread()
{
  int i;
pthread_t thread1, thread2;

    void *kernel_function_1();
    void *kernel_function_2();
for(i=0;i<n_passwords;i<i++) {
   
    
    pthread_create(&thread1, NULL,kernel_function_1, encrypted_passwords[i]);
    pthread_create(&thread2, NULL,kernel_function_2, encrypted_passwords[i]);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
 }
}

void *kernel_function_1(char *salt_and_encrypted){
  int a, b, c;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a,b,c);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
         printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}


void *kernel_function_2(char *salt_and_encrypted){
  int b, d, a;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(b='N'; b<='Z'; b++){
    for(d='A'; d<='Z'; d++){
      for(a=0; a<=99; a++){
        sprintf(plain, "%c%c%02d", b,d,a);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

//time Calculation

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	
	
    		multi_thread();
  	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
