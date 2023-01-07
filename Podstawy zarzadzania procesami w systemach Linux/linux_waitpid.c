//linux_waitpid.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//Funkcja waitpid(): odczekanie do zakończenia wskazanego procesu potomnego

int main(void){

    int pids[2];
    for(int c=0; c<2; c++){
        int pid = fork();
        if(pid == 0){
            printf("Child #%d PID=%d\n", c,getpid());
            sleep(1+c);
            return 1+c;
        }
        pids[c] = pid;
    }
    for(int c = 1; c>= 0; c--){
        int status, child = waitpid(pids[c], &status,0);
        printf("Parents: child #%d exited: PID=%d, retcode=%d\n", c, child, WEXITSTATUS(status));
    }
    return 0;
}






/*
Funkcja waitpid(): odczekanie do zakończenia wskazanego procesu potomnego
    
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *wstatus, int options);

    Działanie:
        ● zawieszenie procesu, który wywołał waitpid(), do chwili zakończenia procesu potomnego o wskazanym 
            identyfikatorze; jeśli w chwili wywołania taki proces potomny nie istnieje, powrót z waitpid() następuje natychmiast
        Parametr:
            ● pid      – id procesu potomnego albo -1 jeśli czeka się na dowolny z procesów potomnych
            ● wstatus  – jak w przypadku wait() 
            ● options  – 0 dla zachowania domyślnego, WNOHANG jeśli waitpid() ma wrócić natychmiast, jeśli wszystkie dzieci są aktywne
        Wynik:
            ● -1 w przypadku błędu, w tym, jeśli nie ma żadnych procesów potomnych albo PID zakończonego dziecka

*/