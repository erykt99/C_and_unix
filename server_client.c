#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>


double RATINGS[40];
int NRATINGS[40];

#define GNIAZDKO_SERWERA "/tmp/gniazdko_serwera3480"


int main() {
    int N_ROUNDS = 100;
    int N_GOODS = 40;
    int a ,b,x,result;
    int CUSTOMERS = 25;
    int status;
	double suma,gh = 0;
    int msg, sock;
    socklen_t serv_len;
    struct sockaddr_un serv_addrstr;
    char buf[BUFSIZ];
    char *r;
    struct timespec timeout = {0, 100000000};

    sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    serv_addrstr.sun_family = AF_UNIX;
    strcpy(serv_addrstr.sun_path, GNIAZDKO_SERWERA);
    unlink(GNIAZDKO_SERWERA);
    serv_len = sizeof(serv_addrstr);
    if(bind(sock, (struct sockaddr *)&serv_addrstr, serv_len) == -1){printf("error");exit(-1);}


    for ( int h = 0; h < CUSTOMERS;h++){
        if(fork() == 0)
         {
            for (int j = 0; j < N_ROUNDS; j++) {
            srand(time(NULL)+j);
		    a = rand() % N_GOODS;
		    b = rand() % 11;
            memcpy(buf, &a, sizeof(int));
		    memcpy(buf+sizeof(int), &b, sizeof(int));
    		sendto(sock, buf, sizeof(buf),0,(struct sockaddr *)&serv_addrstr, serv_len);

     //   nanosleep((struct timespec *)&timeout,(struct timespec *)0);
           }
           close(sock);
	      exit(1);
         }
	}

    while (1) {
        if (gh == CUSTOMERS * N_ROUNDS) break;

        msg = recvfrom(sock, &buf, sizeof(buf), 0, (struct sockaddr*)0, 0);
        if (msg == -1) { printf("error2"); exit(-1); }
        memcpy((void*)&a, (void*)buf, sizeof(int));
        memcpy((void*)&b, (void*)(buf + sizeof(int)), sizeof(int));
        NRATINGS[a]++;
        RATINGS[a] = (((NRATINGS[a] - 1) * RATINGS[a] + b) / NRATINGS[a]);
        gh++;
    }
    close(sock);
    for (int i=0; i < N_GOODS; i++)
    {
     printf("%2d: Ocena: %.2f  Liczba sztuk %2d\n", i, RATINGS[i], NRATINGS[i]);
    suma = suma + NRATINGS[i];
      }
printf("liczba sztuk: %f\n", suma);

}

