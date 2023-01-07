//args.c
#include <stdio.h>


//Wypisanie na stdout wszystkich argumentów programu:
int main(int argc, char **argv)
{
    printf("ARGC: %d \n\n", argc);
	for(int i = 0; i <= argc; i++)
		printf("%2d: %s\n", i, argv[i]);


	return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------
Standard języka C dopuszcza trzy postaci nagłówka funkcji main():
1)bez parametrów:
    int main(void) 
2)z dwoma parametrami:  
    int main(int argc, char **argv)

    argc
        liczba argumentów przekazanych w linii poleceń + 1

    argv
        argumenty (łańcuchy znaków) przekazane do programu, przy czym:

    argv[0] - nazwa programu
    argv[1] - pierwszy argument
        :
    argv[argc-1]  - ostatni argument
    argv[argc] - NULL

3)z  trzema parametrami:
    int main(int argc, char **argv, char **env)
    -----------------------------------------------------------------------------------------------------------------------
*/