// linux_unsetenv.c

#include <stdio.h>
#include <stdlib.h>

void p(char *s) {
	printf("%s\n", s ? s : "(null)");
}
//Nadanie/zmiana/usunięcie wartości zmiennej:
int main(void)
{
	char *nam = "VAR";
	p(getenv(nam));
    setenv(nam,"VAL",0);
	p(getenv(nam));
	unsetenv(nam);
	p(getenv(nam));	
	return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------
Funkcja unsetenv(): usunięcie zmiennej:

#include <stdlib.h>
int unsetenv(const char *name);
    Parametry:
        ● name – nazwa zmiennej
    Wynik:
        ● 0   – powodzenie
        ● -1  – niepowodzenie (errno określa przyczynę) 
-----------------------------------------------------------------------------------------------------------------------
*/