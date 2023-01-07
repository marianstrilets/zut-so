#include <windows.h>
#include <stdio.h>

int main(void) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi[3];
	char argline[50];
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));	
	si.cb = sizeof(si);
	for(int i = 0; i < 3; i++) {
		sprintf(argline, "win_prog.exe Process=%d arg1 arg2", i+1);
		if(CreateProcessA(NULL,argline,NULL,NULL,0,0,"Path=C:\\My\\Path\0\0",NULL,&si,pi+i) == 0){
			printf( "CreateProcess #%d failed (%d).\n", i+1, GetLastError() );
			return 2;
		}
		printf("Process #%d created: handle=%p, identifier=%d\n", i+1, pi[i].hProcess, pi[i].dwProcessId);
	}
	for(int i = 2; i >= 0;  i--) {
		WaitForSingleObject(pi[i].hProcess,INFINITE);
		CloseHandle( pi[i].hProcess );
		CloseHandle( pi[i].hThread );
		printf("Process #%d terminated.\n", i+1);
	}
	return 0;
}