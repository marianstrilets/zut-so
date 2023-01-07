//linux_wait.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//Funkcja wait(): odczekanie do zakończenia dowolnego procesu potomnego

int main(void){
    int pid = fork();

    if(pid == 0){
        printf("\n\tChild with PID=%d\n", getpid());
        sleep(5);
        printf("\n\tChild wakes up\n");
        return 27;
    }else if(pid == -1){
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        return 1;
    }
    printf("parent is waiting for a child to finish\n");
    int status, child = wait(&status);
    printf("Child finished: PID=%d, retcode=%d\n", child, WEXITSTATUS(status));
    return 0;
}

/*
Funkcja wait(): 
    ● rodzic może poczekać, aż proces dziecka zostanie zakończony i wstrzymać swoje działanie do tej chwili
    ● normalnie rodzic wykonuje się niezależnie od dziecka i jest niewrażliwy na fakt jego zakończenia

Funkcja wait(): odczekanie do zakończenia dowolnego procesu potomnego

    #include <sys/wait.h>
    pid_t wait(int *wstatus);

    Działanie:
        ● zawieszenie procesu, który wywołał wait(), do chwili zakończenia dowolnego z jego procesów potomnych; jeśli 
            w chwili wywołania nie istnieje żaden „żywy” proces potomny, powrót z wait() następuje natychmiast
    Parametr:
        ● wstatus – NULL albo wskaźnik na daną, w której wait() umieści kod zakończenia dziecka
    Wynik:
        ● -1 w przypadku błędu, w tym, jeśli nie ma żadnych procesów potomnych albo PID zakończonego dziecka

*/















/*
Funkcja wait(): 
    ● rodzic może poczekać, aż proces dziecka zostanie zakończony i wstrzymać swoje działanie do tej chwili
    ● normalnie rodzic wykonuje się niezależnie od dziecka i jest niewrażliwy na fakt jego zakończenia

Funkcja wait(): odczekanie do zakończenia dowolnego procesu potomnego

    #include <sys/wait.h>
    pid_t wait(int *wstatus);

    Działanie:
        ● zawieszenie procesu, który wywołał wait(), do chwili zakończenia dowolnego z jego procesów potomnych; jeśli 
            w chwili wywołania nie istnieje żaden „żywy” proces potomny, powrót z wait() następuje natychmiast
    Parametr:
        ● wstatus – NULL albo wskaźnik na daną, w której wait() umieści kod zakończenia dziecka
    Wynik:
        ● -1 w przypadku błędu, w tym, jeśli nie ma żadnych procesów potomnych albo PID zakończonego dziecka

*/