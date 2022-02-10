#include <stdio.h>
#include <stdlib.h>


int main ()
{
	int status;
	int n;
        char buf[5];
        char polecenie[5];
    while (1) {
        printf("Podaj polecenie do wykonania [d,s,c,t,q]:\n");
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%s", polecenie);

        if (polecenie [0] == 'q') {break;}

        else if(fork()==0) {
            printf("Tu potomek pid=%d\n", getpid());
            switch (polecenie[0]) {
            case 'd': printf("polecenie d\n");
                                system("date");     
                                break;
            case  's': printf("polecenie s\n");
                                system("sh");
                                break;
            case 'c': printf("polecenie c\n");
                                execlp("xclock","xclock","-update","1",(char *)NULL); 
                                break;
	        case 't': printf("polecenie t\n");
				system("xterm");
				break;
            }
            exit(0); 
        }
        printf("Tu rodzic po utworzeniu potomka.\n");

        switch (polecenie[0]) {
        case 'd':  
                        wait();
                        break;
        case 's': 
                        wait();
                        break;
        case 'c': 
			waitpid(n, &status,0);
                         break;
	    case 't':	wait(n, &status,0);
			break; 
        }
        while(waitpid(-1,NULL, WNOHANG)>0);
    } 
}

