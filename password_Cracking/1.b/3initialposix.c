#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>


int no_of_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$KXXRh1D6ksqio88QK/pSvBWLCzGis8WoVJS7pp5WyThRJy2PguEKjpYk8sr/5M/exImvL/f5tQ/.f0HwInt3W1",
  "$6$KB$AHuS/Amm9SuPTZITWiJwwevl4.yAfJgOUyPT8oYkkr3uccL9ksF0Ea3eHggB8tBgwxwvQZ0zywsh2QTncg7EB/",
  "$6$KB$jekKLoIeTdFWJOzp1mD6B9ZO1gIgCpMynHUPnrKoXS28lb/VyCh0NW1AByS0b1sY3uGfBKK65UqPq2JRj5uIi/",
  "$6$KB$MtvpDndBYKa6MFTtR2KmyEjdUQbL.9yL94q/MHrHXmXFCLzctF6HSBakH5vOcd3MgyjDAr6NrT3A8rbzOIrgs/"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int m, n, o, p;     
  char salt[7];   
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);
 for(m='A'; m<='Z'; m++){
  for(n='A'; n<='Z'; n++){
    for(o='A'; o<='Z'; o++){
      for(p=0; p<=99; p++){
        sprintf(plain, "%C%c%c%02d", m, n, o, p); 
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
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish, 
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
  int i;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  
  for(i=0;i<no_of_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9));




  return 0;
}
