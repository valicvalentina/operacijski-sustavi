#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <stdbool.h>
#include <semaphore.h>

pthread_mutex_t m;
pthread_cond_t red[2];
int prog_vrsta=0;
int broj[2] = {0,0};
int u_redu[2] = {0,0};
int siti[2]={0,0};
int id[2] ={0,0};
char *prog[2] = { "Microsoft", "Linux"};
int N=5;
int zadnjiid[2] = {0,0};



void *funkcija(void *p)
{
   int prog_vrsta = rand() & 1;
   int id;
   
   pthread_mutex_lock(&m);
   u_redu[prog_vrsta]++;
   
     if(zadnjiid[prog_vrsta]>=N){
        zadnjiid[prog_vrsta] = 0;
     }
       id = ++zadnjiid[prog_vrsta];
    
     while(broj[1-prog_vrsta]>0 || ((siti[prog_vrsta]>=N) && (u_redu[1-prog_vrsta]>0))){
            pthread_cond_wait(&red[prog_vrsta], &m);
     }
     
   broj[prog_vrsta]++;
   u_redu[prog_vrsta]--;
   siti[1-prog_vrsta] = 0;
   printf("ulazi %d %s\n",id,prog[prog_vrsta]);
  //if(u_redu[1-prog_vrsta]>0){
  siti[prog_vrsta]++;
  //}
   pthread_mutex_unlock(&m);

   sleep(2);
   
   pthread_mutex_lock(&m);
   broj[prog_vrsta]--;
   printf("izlazi %d %s\n",id,prog[prog_vrsta]);
   
   if(broj[prog_vrsta] ==0){
     pthread_cond_broadcast(&red[1-prog_vrsta]);
   }
   pthread_mutex_unlock(&m);
   } 



int main()
{
 pthread_t thr_id;
 pthread_attr_t attr;
 pthread_mutex_init(&m,NULL);
 pthread_cond_init(&red[0],NULL);
 pthread_cond_init(&red[1],NULL);

 pthread_attr_init(&attr);
 pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
 srand((unsigned int) time(NULL));


             while(1){
                pthread_create(&thr_id,&attr,funkcija,NULL);
                sleep(2);
             }
             
 pthread_mutex_destroy(&m);
 pthread_cond_destroy(&red[0]); 
 pthread_cond_destroy(&red[1]); 
               
               
 return 0;
}






























