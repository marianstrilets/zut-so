// putenv.c

#include <stdio.h>
#include <stdlib.h>

void p(char *s){
    printf("%s\n", s ? s: "(null)");
}

// Nadanie/zmiana wartości zmiennej:
int main(void)
{
    char *nam = "VAR", envstring[20];
    p(getenv(nam));
    sprintf(envstring, "%s = %s", nam, "VAL");
    putenv(envstring);
    p(getenv(nam));
    sprintf(envstring, "%s=", nam);
    putenv(envstring);
    p(getenv(nam));

    return 0;
}

/*
-----------------------------------------------------------------------------------------------------------------------
Funkcja putenv(): utworzenie, modyfikacja lub usunięcie zmiennej:

#include <stdlib.h>
int putenv(const char *envstring);
    Parametry:
        ●  envstring – łańcuch określający czynność do wykonania:
        "NAME=VALUE"  – nadanie zmiennej NAME wartości VALUE
        "NAME"       – usunięcie zmiennej NAME
    Wynik:
        ● 0  – powodzenie
        ● -1  – niepowodzenie (errno określa przyczynę) 
-----------------------------------------------------------------------------------------------------------------------
*/

