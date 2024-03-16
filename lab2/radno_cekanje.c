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
int Id;
int Id2;
int Id3;
int *ZajednickaVarijabla;
int *ZajednickaVarijabla2;
int *ZajednickaVarijabla3;
int broj;
int br;
int l;
int brojac;
FILE *ispis;
pthread_t thr_id[1];

void *Izlazna(void *brojac)
{   
   
  while((*((int*)brojac))!=0){
 
      do {
        int z;
         z= *ZajednickaVarijabla;
      } while((l == 0) || (l==1));
   
   
     if(*ZajednickaVarijabla2==2){
        printf("IZLAZNA DRETVA: broj upisan u datoteku %d\n", l);
        ispis = fopen("ispis.txt","r+");
        int zadnji;
        fseek(ispis, 0L, SEEK_END);        
        fprintf(ispis,"%d\n",l);
        fclose(ispis);
        br=0;
        l=0;
        (*((int*)brojac))--;
        *ZajednickaVarijabla = 0;
        *ZajednickaVarijabla2 = 0;
     }
     
  } 
 
}

void *Ulazna(void)
{
  
    if(brojac !=0 && (*ZajednickaVarijabla2==0)){
       int i;
    
         do {
            i = *ZajednickaVarijabla;
            } while (i != 0);
            
   int sekunda;
   sekunda = rand()%5 + 1;
   sleep(sekunda);
   i=rand()%100 + 1;
   printf("\n");
   printf("ULAZNA DRETVA: broj %d\n", i);
   *ZajednickaVarijabla = i;
   *ZajednickaVarijabla2=1;
   brojac--;
   
   } 
   
       if(brojac==0){ 
         exit(0);
       }
}


 void brisi(int sig)
{

   (void) shmdt((char *) ZajednickaVarijabla);
   (void) shmctl(Id, IPC_RMID, NULL);
   (void) shmdt((char *) ZajednickaVarijabla2);
   (void) shmctl(Id2, IPC_RMID, NULL);
    (void) shmdt((char *) ZajednickaVarijabla3);
   (void) shmctl(Id3, IPC_RMID, NULL);
   
   exit(0);
   exit(0);
   exit(0);

}

 int main(int argc, char *argv[]){
 
    br=0;
    l=0;
    sscanf(argv[1],"%d",&broj);
    brojac = broj;
    
    printf("Pokrenuta RADNA DRETVA\n");
    srand(time(NULL));
    
     /* zauzimanje zajedničke memorije */
    ZajednickaVarijabla = (int *) shmat(Id, NULL, 0);
   Id = shmget(IPC_PRIVATE, sizeof(int), 0600);
   
         if (Id == -1){
           exit(1);  
         }
    
   ZajednickaVarijabla2 = (int *) shmat(Id2, NULL, 0);
   Id2 = shmget(IPC_PRIVATE, sizeof(int), 0600);
   
         if (Id2 == -1){
            exit(1); 
         } 
    
   ZajednickaVarijabla3 = (int *) shmat(Id3, NULL, 0);
   Id3 = shmget(IPC_PRIVATE, sizeof(int), 0600);
   
        if (Id3 == -1){
           exit(1);  
        }
         
     ZajednickaVarijabla = (int *) shmat(Id, NULL, 0);
     ZajednickaVarijabla2 = (int *) shmat(Id2, NULL, 0);
     ZajednickaVarijabla3 = (int *) shmat(Id3, NULL, 0);
    *ZajednickaVarijabla=0;
    *ZajednickaVarijabla2=0;
    *ZajednickaVarijabla3=0;
   
   int k = fork();
   
      if (k == 0) { 
        printf("Pokrenuta ULAZNA DRETVA\n");
        int b = *ZajednickaVarijabla3;
        b++;
        *ZajednickaVarijabla3 = b;
      }
      
       if (k !=0) {
      
            if (pthread_create(&thr_id[0], NULL, Izlazna, &brojac) != 0) {
                 printf("Greska pri stvaranju dretve!\n");
                 exit(1);
          }
          
        printf("Pokrenuta IZLAZNA DRETVA\n");
        int b = *ZajednickaVarijabla3;
         b++;
        *ZajednickaVarijabla3 = b;
   
     } 
 
   if((*ZajednickaVarijabla3) = 2 ){
      
       while(brojac!=0){
    
       if ((k==0) && (*ZajednickaVarijabla == 0)) {
             Ulazna();
   
       } else {
             
             if(br == 0 && brojac!=0){
          
              do {
                 l= *ZajednickaVarijabla;
                 l++;
                 } while((l == 1) || (l == 0));
   
               if((*ZajednickaVarijabla2==1) && (br==0)&&(l!=0)){
   printf("RADNA DRETVA: procitan broj %d i povecan na %d\n",l-1,l);
                    br = 1;
                    *ZajednickaVarijabla2=2;
                }
           } 
      }
   }
   
 }
   (void) wait(NULL);
   pthread_join(thr_id[0], NULL);
   printf("\n");
   printf("Zavrsila RADNA DRETVA\n");
   printf("Zavrsila ULAZNA DRETVA\n");
   printf("Zavrsila IZLAZNA DRETVA\n");
   brisi(0);
   return 0;
 }
