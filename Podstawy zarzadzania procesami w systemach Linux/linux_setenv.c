// linux_setenv.c
#include <stdio.h>
#include <stdlib.h>

//Nadanie/zmiana wartości zmiennej:
int main(void)
{
	char *nam = "VAR";
	char *val = getenv(nam);
	printf("%s\n", val ? val : "(null)");  
	setenv(nam,"VAL",0);
	printf("%s\n", getenv(nam));  
	return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------
Funkcja setenv(): utworzenie nowej zmiennej bądź modyfikacji zmiennej już istniejącej:

#include <stdlib.h>
int setenv(const char *name, const char *value, int overwrite);
    Parametry:
        ●  name – nazwa zmiennej
        ●  value – wartość zmiennej
        ●  overwrite – jeśli różne od zera, wyraża zgodę na nadpisanie istniejącej wartości zmiennej
    Wynik:
        ● 0  – powodzenie
        ● -1  – niepowodzenie (errno określa przyczynę) 
        Uwaga: jeśli overwrite==0 i zmienna name już istnieje, funkcja zwraca 0. 
-----------------------------------------------------------------------------------------------------------------------
*/