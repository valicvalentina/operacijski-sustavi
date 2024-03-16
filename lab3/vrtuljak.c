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

#define BR_POSJETITELJA          25
#define N           5
sem_t *UDIUVRTULJAK;
sem_t *SPREMAN;
sem_t *GOTOVO;
sem_t *IZASAO;
int *kraj;
void posjetitelj(int id)
{

   sem_wait(UDIUVRTULJAK);
   printf("sjedi\n");
   
   sem_post(SPREMAN);
   sem_wait(GOTOVO);
   
   printf("ustani\n");
   
   
   sem_post(IZASAO);
  
     exit(0);
     
 }
 
 
 int main()
 {
 
 int ID1,ID2,ID3,ID4,i,id[BR_POSJETITELJA];
 pid_t pid;
 int krajnji = BR_POSJETITELJA/N;
 
 ID1 = shmget(IPC_PRIVATE, sizeof(sem_t) + sizeof(int), 0600);
 UDIUVRTULJAK = shmat(ID1,NULL,0);
 shmctl(ID1, IPC_RMID,NULL);
 
 ID2 = shmget(IPC_PRIVATE, sizeof(sem_t) + sizeof(int), 0600);
 SPREMAN = shmat(ID2,NULL,0);
 shmctl(ID2, IPC_RMID,NULL);
 
 ID3 = shmget(IPC_PRIVATE, sizeof(sem_t) + sizeof(int), 0600);
 GOTOVO = shmat(ID3,NULL,0);
 shmctl(ID3, IPC_RMID,NULL);
 
 ID4 = shmget(IPC_PRIVATE, sizeof(sem_t) + sizeof(int), 0600);
 IZASAO = shmat(ID4,NULL,0);
 shmctl(ID4, IPC_RMID,NULL);
 
 
 kraj = (int *) (IZASAO + 1);
 sem_init(UDIUVRTULJAK,1,0);
 sem_init(SPREMAN,1,0);
 sem_init(GOTOVO,1,0);
 sem_init(IZASAO,1,0);
 
 *kraj=0;
 
 
 for(i=0;i<BR_POSJETITELJA;i++){
      pid = fork();
 
 if(pid==0) {
     id[i]=i+1;
     posjetitelj(id[i]);
   }
 else if(pid==-1){
   perror("Greska u stvaranju");
   exit(1);
   }
   
   }
     int j=0;
  while(*kraj==0)
 {
     j++;
     
     for(i=0;i<N;i++){ 
        sem_post(UDIUVRTULJAK);
     }
     
     for(i=0;i<N;i++){ 
        sem_wait(SPREMAN);
     }
  
  sleep(1);
  printf("pokreni vrtuljak\n");
  sleep(2);
  printf("zaustavi vrtuljak\n");
  sleep(1);
  
    for(i=0;i<N;i++){ 
       sem_post(GOTOVO);
    }
 
    for(i=0;i<N;i++){ 
       sem_wait(IZASAO);
    }
 
 
    printf("\n");
    
    if(j==krajnji){
     *kraj=1;
    }
  
  }
 
  for(i=0;i<BR_POSJETITELJA;i++){
    wait(NULL);
 }
 
 sem_destroy(UDIUVRTULJAK);
 sem_destroy(SPREMAN);
 sem_destroy(GOTOVO);
 sem_destroy(IZASAO);
 
 shmdt(UDIUVRTULJAK);
 shmdt(SPREMAN);
 shmdt(GOTOVO);
 shmdt(IZASAO);
 
 return 0;
 
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
