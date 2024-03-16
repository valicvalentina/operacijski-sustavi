#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
int broj;
FILE *obrada;
FILE *status;
void obradi_sigint(int sig);
void obradi_sigterm(int sig);
void obradi_sigusr1(int sig);
int dobro=1;

int main()
{
  int x;
  struct sigaction act;
  
 
    act.sa_handler = obradi_sigusr1; 
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGTERM); 
    act.sa_flags = 0; 
    sigaction(SIGUSR1, &act, NULL); 
    
    act.sa_handler = obradi_sigterm;
    sigemptyset(&act.sa_mask);
    sigaction(SIGTERM, &act, NULL);
    
    act.sa_handler = obradi_sigint;
    sigaction(SIGINT, &act, NULL);
    
    
   printf("pid = %ld\n", (long) getpid());
   status = fopen("status.txt","r+");
   obrada = fopen("obrada.txt","r+");
   
   if(status==NULL){ 
   exit(1);
   }
    if(obrada==NULL){ 
   exit(1);
   }
  
  while(dobro==1){
     fscanf(status, "%d", &broj);
     
         if(broj>0){
             broj = broj + 1;
             printf("%d\n", broj);
             x = pow(broj,2);
             fseek(obrada, 0L, SEEK_END);
             fprintf(obrada,"%d\n", x);
             fseek(status, 0L, SEEK_SET);
             int i=0;
             fprintf(status,"%d",i);
          }
  
          if(broj==0){
          int z;
            while(fscanf(obrada, "%d", &z)!=EOF){
               broj=z;
            }
            
          fseek(status, 0L, SEEK_SET);
          int i=0;
          fprintf(status,"%d\n",i);
          broj= ((int)sqrt((double)broj))+1;
          x = pow(broj,2);
          printf("%d\n", broj);
          fprintf(obrada,"%d\n", x);
          }
          
          for(int j=0;j<5;j++){
          sleep(j);
       }
    
     }
   fclose(status);
   fclose(obrada);
   return 0;
}
   
   
   
  void obradi_sigusr1(int sig)
  {
   printf("%d\n", broj);
 }
    
   void obradi_sigterm(int sig)
   {
    fseek(status, 0L, SEEK_SET);
    fprintf(status,"%d",broj);
    dobro=0;
   }   
   
   void obradi_sigint(int sig)
   {
    exit(1);
   }
   
   
   








