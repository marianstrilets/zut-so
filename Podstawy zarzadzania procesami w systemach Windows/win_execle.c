#include <process.h>
#include <stdio.h>

int main(int argc, char *argv[], char **envp) {
	char *myenv[2] = { 
	   "Path=This Is The Path I Like.",
        NULL
	};
	execle("win_prog.exe", "win_prog.exe", "arg1", "arg2", NULL, myenv);
    printf("Something really bad happened - we should not be here!\n");
    return 1;
}