// SO IS1 214b LAB09
// Marian Strilets
// sm51174@zut.edu.pl

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define MYPATH "Path=D:\\___ZUT_3_semestr____________\\Systemy operacyjne\\LABORATORIA\\LAB9\\51174.so.lab09.exe "


int main(int argc, char **argv) {

	//--------------------------------------- ERROR 1 -----------------------------------------
	// sprawdzenie, czy program został uruchomiony z dokładnie jednym argumentem
	if(argc != 2){
		if(argc < 2){
    	    fprintf(stderr, "\n\t\tBez argumentow \n\t\tERROR: 1\n\n");
		    return 1;
    	} else if(argc > 2){
    	    fprintf(stderr, "\n\t\tWiecej jednego argumenta \n\t\tERROR: 1\n\n");
    	    return 1;
    	}
	}else{
		int arguments = 0;
    	arguments = atoi(argv[1]);

		if(arguments > 0 && arguments <= 13){	
			// jeśli otrzymany argument jest równy 1 lub 2
			if(arguments == 1 || arguments == 2){
        		//fprintf(stderr, "\n\t\tArgument jest 1 lub 2 \n\t\tERROR: 1\n\n");
	    		return 1;
    		}

			// Tworze zmienne dla parametrów funkcji CreateProcessA().
		    STARTUPINFO si[2];
		    PROCESS_INFORMATION	pi[2];
		    char argline[50];
			memset(si, 0, sizeof(si));
			memset(pi, 0, sizeof(pi));
			si[0].cb = sizeof(si[0]);
			si[1].cb = sizeof(si[1]);		 

			          

		    for (int i = 0; i < 2; i++) {	
				sprintf(argline, "51174.so.lab09.exe %d", arguments - i - 1);
				if (CreateProcessA(NULL, argline, NULL,NULL, 0, 0, MYPATH, NULL, &si[i],&pi[i]) == 0) {
					printf(" Blad podczas tworzenia procesu potomnego: #%d ERROR: %s\n",  (i + 1), GetLastError());
				    return 2;
				} 
		    }

		    int sum = 0;
		    for (int i = 0; i < 2; i++) {
				
		        WaitForSingleObject(pi[i].hProcess, INFINITE);   // Oczekiwanie na zakończenie obu procesów potomnych             
		        DWORD exit_code;
		       	GetExitCodeProcess(pi[i].hProcess, &exit_code);
	
		       	printf("%d\t%d\t%d\t%d\n", GetCurrentProcessId(), GetProcessId(pi[i].hProcess), (arguments - i - 1), exit_code);
		    	sum += exit_code;
				CloseHandle(pi[i].hProcess);
		    	CloseHandle(pi[i].hThread);
			}
			printf("%d\t\t\t%d\n", GetCurrentProcessId(), sum); 
			printf("\n");
			return sum;
		}
		
		//--------------------------------------- ERROR 2 -----------------------------------------
		// sprawdzenie, czy otrzymany argument jest liczbą naturalną
		char* endptr;
		long value = strtol(argv[1], &endptr, 10);
		if (*endptr != '\0') {
			fprintf(stderr, "\n\t\tArgument nie jest liczba \n\t\tERROR: 2\n\n");
			return 2;
		}
	
		//--------------------------------------- ERROR 3 -----------------------------------------
		// sprawdzenie, czy otrzymany argument jest liczbą  z przedzialu <1..13>
		if(arguments < 0 || arguments > 13) {
	        fprintf(stderr, "\n\t\tArgument nie jest z przedzialu <1..13> \n\t\tERROR: 3\n\n");
		    return 3;
	    }                         
	}
	return 0;
}