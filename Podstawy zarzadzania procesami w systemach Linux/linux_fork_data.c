//linux_fork_data.c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char text[] = "PARENT";
//Rozłączność danych rodzica i dziecka: 

int main(void){
    
    int value = fork();

    if(value == 0){         //child
        strcpy(text, "CHILD");
        printf("\n\tI am a child: %s\n\n", text);
        return 0;
    }else if(value > 0){    //parent
        sleep(1);
        printf("\n\tI am a parent: %s\n", text);
        return 0;
    }else{                  //failure
        printf("fork(0 failed - %s\n", strerror(errno));
        return 1;
    }

}




/*
Funkcja fork(): 
    ● w trakcie wykonania funkcji fork() nowy proces otrzymuje od rodzica kopię jego danych
    ● kod procesu najczęściej nie podlega kopiowaniu, ponieważ z reguły jest przechowywany w pamięci 
        „execute only”, której zawartość nie może być mody㷨kowana – tym samym dowolna liczba procesów 
        potomnych może posługiwać się tym samym kodem
    ● obszary danych dziecka i rodzica są rozłączne
*/