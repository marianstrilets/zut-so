//linux_fork.c

//Rozdwojenie procesu:
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
    
    int value = fork();

    //--------------------child----------------
    if(value == 0){     //child
        printf("\n\n\tI am a child %d of parent %d\n\n", getpid(), getppid());
        return 0;
    //--------------------parent----------------
    }else if(value > 0){ 
        printf("\n\n\tI am a parent %d of child %d\n\n", getpid(), value);
        return 0;
    //--------------------failure----------------    
    }else{                 
        printf("\n\n\t fork() failed - %s \n\n", strerror(errno));
        return 1;
    }
}


/*
-----------------------------------------------------------------------------------------------------------------------
Funkcja fork(): utworzenie nowego procesu

#include <unistd.h>
pid_t fork(void);

    Działanie:
        ● zatrzymanie procesu, który wywołał fork()
        ● sklonowanie procesu w efekcie czego powstaje nowy proces potomny (dziecko), który jest idealną kopią procesu 
            macierzystego (rodzica)
        ● wznowienie obu procesów (rodzica i dziecka)
        ● od tego momentu oba procesy pracują niezależnie i równolegle
    Wynik:
        ● -1 – błąd: proces potomny nie został utworzony
        ● =0   – proces potomny został utworzony, a proces, który otrzymał tę wartość, jest dzieckiem
        ● >0 – proces potomny został utworzony, proces, który otrzymał tę wartość jest rodzicem, a sama wartość jest 
            identyࢰkatorem dziecka
-----------------------------------------------------------------------------------------------------------------------

Funkcje getpid(): pobranie identyfikatora procesu bieżącego

    #include <sys/types.h>
    #include <unistd.h>    
    pid_t getpid(void);

    Wynik:
        ● identyfikator procesu, który wywołał funkcję (wywołanie zawsze kończy się sukcesem)
-----------------------------------------------------------------------------------------------------------------------

Funkcje getppid(): pobranie identyfikatora procesu macierzystego

    #include <sys/types.h>
    #include <unistd.h>
    pid_t getppid(void);

    Wynik:
        ● identy㷨kator procesu, który utworzył proces wywołujący funkcję (wywołanie zawsze kończy się 
            sukcesem)
-----------------------------------------------------------------------------------------------------------------------

Funkcja sleep(): zawieszenie procesu wywołującego

    #include <unistd.h>
    unsigned int sleep(unsigned int seconds);

    Działanie:
        ● zawieszenie procesu, który wywołał sleep() na co najmniej tyle sekund, ile podano w argumencie
    Parametr:
        ● seconds – liczba sekund, na które należy uśpić proces
    Wynik:
        ● 0 jeśli cały żądany czas upłynął
-----------------------------------------------------------------------------------------------------------------------
*/