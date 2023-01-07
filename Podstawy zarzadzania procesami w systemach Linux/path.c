//path.c

#include <stdio.h>
#include <stdlib.h>

//Wypisanie na stdout wartości zmiennej PATH
//(zmienna PATH istnieje i w Linuksie, i w Windows, chociaż z inną składnią):

int main(void) {
	char *nam = "PATH";
	char *val = getenv(nam);
	if(val == NULL)
		printf("\n\t%s undefined\n\n", nam);
	else 
		printf("\n\t%s=%s\n\n", nam, val);	
	return 0;
}
/*
-----------------------------------------------------------------------------------------------------------------------

Funkcja getenv(): pobranie łańcucha wskazanej zmiennej środowiska:

	#include <stdlib.h>
	char *getenv(char *name);

	Parametry:
		●  name – nazwa żądanej zmiennej
	Wynik:
		● NULL jeśli w środowisku nie ma zmiennej o podanej nazwie
		● w przeciwnym przypadku wskaźnik na łańcuch przechowujący zmienną
-----------------------------------------------------------------------------------------------------------------------
*/