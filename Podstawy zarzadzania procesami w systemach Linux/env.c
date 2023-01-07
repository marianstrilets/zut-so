//env.c
#include <stdio.h>

// Wypisanie na stdout wszystkich dostępnych zmiennych środowiska:
 
int main(int argc, char *argv[], char **env) {
 	char **p = env;
 	int    n = 1;
 	while(*p) 
 		printf("%2d: %s\n", n++, *p++);
	return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv, char **env)
    env
        jak argv, ale jest tablicą wskaźników na łańcuchy tworzące tzw. zmienne środowiska 
        (ang. environment variables); w ostatnim elemencie tablicy znajduje się NULL
    Zmienne środowiska:
        ● łańcuchy postaci "NAME=VALUE", przechowywane wewnątrz obszaru pamięci każdego procesu
        ● każdy proces ma własną kopię pełnego zestawu zmiennych
        ● proces może mody誸kować własny zestaw zmiennych (usuwać zmienne, dodawać zmienne, zmieniać 
            ich wartość), ale nie ma dostępu do zmiennych innych procesów
        ● nowy proces (zwykle) otrzymuje kopię środowiska swojego rodzica, ale można to zmienić 
-----------------------------------------------------------------------------------------------------------------------
*/