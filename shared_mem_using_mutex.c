#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>
#include <pthread.h>

int N_GOODS = 40, CUSTOMERS =20, N_ROUNDS = 1000000, RATING = 10,a ,b;
int status;
int      shmid; 
double sum =0;
struct mem {
	int NRatings[40];
	double Ratings[40];
	pthread_mutexattr_t attr[40];
	pthread_mutex_t mut[40];
};

struct mem *shm;

int main(){
static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

shmid = shmget (1245, sizeof( struct mem), IPC_CREAT | 0600 );
shm = ((struct mem*) shmat(shmid, NULL, 0));

for (int i = 0; i<N_GOODS; i++){shm->Ratings[i]=0; shm->NRatings[i]=0;};

for (int i = 0; i<N_GOODS; i++){
pthread_mutexattr_init(&shm->attr[i]);
pthread_mutexattr_setpshared(&shm->attr[i], PTHREAD_PROCESS_SHARED);
pthread_mutex_init(&shm->mut[i], (&shm->attr[i]));
};

st_time = times(&st_cpu);

for ( int h = 0; h < CUSTOMERS;h++){
 if(fork() == 0)
  {
   for (int j = 0; j < N_ROUNDS; j++) {
    srand(time(NULL)+j);
    a = rand() % N_GOODS;
    b = rand() % 11;

    pthread_mutex_lock(&shm->mut[a]);

    shm->NRatings[a]++;
    shm->Ratings[a] = ((((shm->NRatings[a])-1) * shm->Ratings[a] + b) /shm->NRatings[a]);

    pthread_mutex_unlock(&shm->mut[a]);
	}
    exit(1);
    }
}
	
for ( int l =0;l<=CUSTOMERS;l++){wait(&status);}

en_time = times(&en_cpu);


for (int i=0; i < N_GOODS; i++)
{
 printf("%-2d. NRATINGS: %-3d Ratings: %-3f \n", i, shm->NRatings[i], shm->Ratings[i]);
 sum = sum + ((*shm).NRatings[i]);
}
printf("\nSuma: %lf \n",sum);
for (int i=0; i<N_GOODS;i++){
pthread_mutex_destroy(&shm->mut[i]);};
shmdt(NULL);

printf("Real Time: %.2fs, User Time %.2fs, System Time %.2fs\n",
	(float)(en_time - st_time)/100,
        (float)(en_cpu.tms_cutime - st_cpu.tms_cutime)/100,
        (float)(en_cpu.tms_cstime - st_cpu.tms_cstime)/100);
return 0;
}
