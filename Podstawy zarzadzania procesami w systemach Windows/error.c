//error.c
// Rozpoznawanie błędów wywoływanych przez wywołania systemowe:

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(void) {
//Funkcja malloc() zwraca wskaźnik do przydzielonej wielkości pamięci. Jeśli żądanie nie powiedzie, zwraca NULL.
	void *p = malloc(-10);

//zmienna errno ustawiana jest przez funkcje systemowe i podaje dokładną przyczynę ewentualnego niepowodzenia
//(zwykle funkcje systemowe zwracają -1 albo NULL w sytuacji błędu)
    int errno_p = errno;
	if(p == NULL) {
		
        printf("\n\t\tERNNO:\n");

		printf("\terrno=%d: '%s'\n\n\n", errno_p, strerror(errno_p));
	}else{
        printf("\n\tYou are success alocate memory!\n\n");
    }
	return 0;
}
