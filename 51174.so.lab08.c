// SO IS1 214b LAB08
// Marian Strilets
// sm51174@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
    if (argc != 2) {
        if(argc < 2){
            fprintf(stderr, "\n\t\tBez argumentow \n\t\tERROR: 1\n\n");
		    return 1;
        } else{
            fprintf(stderr, "\n\t\tWiecej jednego argumenta \n\t\tERROR: 1\n\n");
            return 1;
        }		
	} else{
        int arguments = 0;
        arguments = atoi(argv[1]);

        if(arguments == 0){
            fprintf(stderr, "\n\t\tArgument nie jest liczba naturalna \n\t\tERROR: 2\n\n");
		    return 2;
        } else{
            if(arguments > 0 && arguments <=13){
                if(arguments == 1 || arguments == 2){
                    fprintf(stderr, "\n\t\tArgument jest 1 lub 2 \n\t\tERROR: 1\n\n");
		            return 1;
                }else{
                    arguments = atoi(argv[1]);

                    while(1 < arguments){ 
                        int pids[2];
                        
                        for(int c = 0; c < 2; c++) {
                            
                            int pid = fork();                        
                            if(pid == 0) {  
                                                               
                                return 1+c;
                            }
                            pids[c] = pid;
                            execv("./51174.so.lab08", argv[1]);
                        }

//------------------ Print --------------------------------------------------------------------------------------------                        
                        int sum =0;
                        for(int c = 1; c >= 0; c--) {
                            int status, child = waitpid(pids[c],&status,0);
                            
                            
                            printf("\t%d\t%d\t%d\t%d\n", getpid(), pids[c], arguments - c, WEXITSTATUS(status));
                            sum += WEXITSTATUS(status); 
                        }
                            printf("\t%d\t\t\t%d\n", getpid(), sum);

                        arguments--;                         
                        printf("\n");
                    }
                    return 0;
                }                
            }else{
                fprintf(stderr, "\n\t\tArgument nie jest z przedzialu <1..13> \n\t\tERROR: 3\n\n");
		        return 3;
            }
        }
    }
	return 0;
}