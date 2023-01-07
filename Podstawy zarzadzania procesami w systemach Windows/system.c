//system.c
#include <stdlib.h>
#include <stdio.h>
	
// Uruchomienie polecenia „dir” za pośrednictwem powłoki
int main(void) {
	int value = system(NULL);
    printf("\n\tShell %s \n\n", value ? "available" : "not available");

    if(value != 0){
        value = system("dir");
        printf("\n\tShell returned %d\n\t", value); //0
    }

	return 0;
}
/*
-----------------------------------------------------------------------------------------------------------------------
Funkcja system(): wykonanie polecenia powłoki

#include <stdlib.h>
int system(const char *command);

    Parametry:
        ● command – NULL albo polecenie powłoki wraz z ewentualnymi argumentami; składnia polecenia musi być 
        zgodna z konwencjami systemu operacyjnego; argument o wartości NULL używany jest do sprawdzenia 
        dostępności powłoki 
    Wynik:
        ●  jeśli command == NULL:
            ● =0 – powłoka nie jest dostępna
            ● ≠0 – powłoka jest dostępna
        ● jeśli command !=NULL:
            ● -1 – wykonanie polecenia zakończyło się niepowodzeniem
            ● ≥0 – kod powrotu zwrócony przez powłokę 
-----------------------------------------------------------------------------------------------------------------------

Interpretacja wyniku funkcji system() zależy od systemu.

{Windows}
    Wynik jest wprost kodem powrotu z powłoki albo uruchomionego przez nią programu.
{Linux}
    ● 8 starszych bitów wyniku jest kodem powrotu z powłoki albo uruchomionego przez nią programu
    ● 8 młodszych bitów jest tzw. termination reason code
    ● ustalenie faktycznego kodu powrotu umożliwia makro WEXITSTATUS():

    int ret = system(cmd);
    int aret = WEXITSTATUS(ret);
-----------------------------------------------------------------------------------------------------------------------
*/