#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>

int main(void) {
	char *myenvp[] = {"Path=PATHx",	NULL };
	char *myargv[] = {"win_prog.exe", "processx",	NULL };
	for(int i = 0; i < 3; i++) {
		myargv[1][strlen(myargv[1]) - 1] = '1' + i;
		myenvp[0][strlen(myenvp[0]) - 1] = '1' + i;
		int ret = spawnve(_P_NOWAIT, "win_prog.exe", myargv, myenvp);
		printf("Spawn #%d: retcode=%d", i+1, ret);
		if(ret < 0) printf(" errno=%d", errno);
		printf("\n");
	}
	return 0;
}