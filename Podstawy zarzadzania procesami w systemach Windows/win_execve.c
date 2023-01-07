#include <stdio.h>
#include <stdlib.h>
#include <process.h>

int main(int argc, char *argv[], char **envp) {
	char *myargv[5];
	myargv[0] = "win_prog.exe";
	for(int i = 1; i < 4; i++) {
		myargv[i] = malloc(2);
		myargv[i][0] = '0' + i;
		myargv[i][1] = '\0';
	}
	myargv[4] = NULL;
	execve("win_prog.exe", myargv, envp);
	printf("Something really bad happened - we should not be here!\n");
	return 1;
}