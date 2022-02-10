#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>

    int N_ROUNDS = 1000000;
    int N_GOODS = 40;
    int a ,b;
    int CUSTOMERS = 20;
    int status;
	double suma;
    double *buf;
 


int main() {
       static clock_t st_time;
    static clock_t en_time;
    static struct tms st_cpu;
    static struct tms en_cpu;
    int shmid = shmget(2211,(40*sizeof(double) + 40*sizeof(int)), IPC_CREAT|0600);
    buf = (double *)shmat(shmid,0,0);
    for (int g = 0; g<=N_GOODS*2;g++)
     {
      buf[g] = 0;
     }
    st_time = times(&st_cpu);


    zakupy();
    

    en_time = times(&en_cpu);




    for (int k = 0; k <40; k++) {
    printf("RATING %d [%lf] NRATINGS %d [%lf]\n",k, buf[k+N_GOODS],k ,buf[k]);
	suma +=buf[k];
    }
	printf("Suma: %lf\n",suma);
    printf("Real Time: %.2fs, User Time %.2fs, System Time %.2fs\n",
        (float)(en_time - st_time)/100,
        (float)(en_cpu.tms_cutime - st_cpu.tms_utime)/100,
        (float)(en_cpu.tms_cstime - st_cpu.tms_stime)/100);
return 0;
}

int shopping(){
    for ( int h = 0; h < CUSTOMERS;h++){
        if(fork() == 0)
         {
            for (int j = 0; j < N_ROUNDS; j++) {
            srand(time(NULL)+j);
		    b = rand() % N_GOODS;
		    a = rand() % 11;
           	buf[b] +=1;
            buf[b+N_GOODS]= (((buf[b]-1)*buf[b+N_GOODS] + a)/buf[b]);
           }
	exit(1);
         }
	}

    for ( int l =0;l<=CUSTOMERS;l++){wait(&status);}
return 0;
}
