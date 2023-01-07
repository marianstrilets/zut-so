//linux_program.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Program doświadczalny – usypia na podaną liczbę sekund i odlicza czas

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "usage: %s seconds\n", argv[0]);
        return 1;
    }
    char *endptr;
    int secs = strtol(argv[1], &endptr, 10);
    if(secs <= 0 || *endptr != '\0'){
        fprintf(stderr, "argument must be an int greater than 0 - exiting\n");
        return 2;
    }
    printf("#%d will wait %d seconds...\n", getpid(), secs);
    for(int i = 0; i < secs; i++) {
        printf("#%d -> %d...\n", getpid(), secs - i);
        sleep(1);
    }
    printf("#%d completed\n", getpid());
    return 0;
}


//int execl(char *path, char *arg, ... /* NULL */);
//int execle(char *path, char *arg, .../* NULL */, char *envp[]);
//int execlp(char *file, char *arg, ... /* NULL */);
//int execv(char *path, char *argv[]);
//int execve(char *file, char *argv[], char *envp[]);
//int execvp(char *file, char *argv[]);
//int execvpe(char *file, char *argv[], char *envp[]);
/*
● przyrostek l oznacza, że funkcja używa zmiennej listy argumentów do przekazania parametrów do uruchamianego 
    programu (NULL kończy listę)
● przyrostek p oznacza, że funkcja używa zmiennej środowiska PATH do znalezienia pliku wykonalnego; funkcje bez tego 
    przyrostka muszą podać pełną ścieżkę do pliku
● przyrostek e oznacza, że funkcja preparuje nowe środowisko do uruchamianego programu; funkcje bez tego przyrostka 
    kopiują istniejące środowisko
● przyrostek v oznacza, że funkcja używa tablicy do przekazania argumentów do programu 
*/


/*
Rodzina funkcji execxx(): wymiana kodu procesu na pobrany z pliku
    ● funkcje z rodziny execxx() służą do załadowania z pliku nowego kodu i uruchomienie go w 
        miejsce obecnie wykonywanego
    ● oznacza to, że funkcje tej rodziny nie wracają do miejsca wywołania, ponieważ z chwilą ich 
        pomyślnego wykonania miejsce wywołania przestaje istnieć
    ● PID procesu, który wymienia kod, pozostaje bez zmian
    ● w przypadku błędu wszystkie funkcje tej rodziny zwracają -1
    ● każda funkcji jest odpowiedzialna za przygotowanie kompletnej tablicy argv uruchomianego 
        procesu (włącznie z argv[0])
    ● w zależności od funkcji robi się to albo podając kolejne argumenty wywołania, albo wskazując 
        tablicę łańcuchów (zakończoną przez NULL), która zostanie przekopiowana do uruchamianego 
        programu
*/