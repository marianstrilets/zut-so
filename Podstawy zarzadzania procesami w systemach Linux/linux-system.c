//linux_system.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Uruchomienie polecenia „false” za pośrednictwem powłoki
int main(void){
    int value = system(NULL);
    printf("\n\tShell %s", value ? "is available\n\n" : "is not available\n\n"); //...is available

    if(value != 0){
        value = system("false");
        printf("\n\tShell returned %d\n\n", value); //256
    }

    return 0;
}
