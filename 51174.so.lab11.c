// SO IS1 214b LAB11
// Marian Strilets
// sm51174@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#define MAX_THREADS 100             // Maksymalna liczba wątków
#define MAX_ITERATIONS 1000000000   // Maksymalna liczba wyrazów ciągu Wallisa

HANDLE mutex;               // Mutex chroniący dostęp do zmiennej global_result
double global_product = 1;  // Globalna zmienna przechowująca iloczyn wyrazów ciągu Wallisa


//Struktura przekazywana do każdego wątku
typedef struct {
    int start_index;    // Indeks pierwszego wyrazu ciągu dla danego wątku
    int end_index;      // Indeks ostatniego wyrazu ciągu dla danego wątku
}ThreadArgs ;

double wallisa(int start, int end ){
    double result = 1;
    for (int i = start; i <= end; i++) {
        result *= ((double) (2*i)) / ((double) (2*i - 1));
        result *= ((double) (2*i)) / ((double) (2*i + 1));
    }
    result*=2;
    return result;
}

void function_mutex(double thread_product){
    WaitForSingleObject(mutex, INFINITE);
    global_product *= thread_product;
    ReleaseMutex(mutex);
}

DWORD WINAPI program2pthread(LPVOID args) {
    ThreadArgs *thread_args = (ThreadArgs *) args;

    int start_index = thread_args->start_index;
    int end_index = thread_args->end_index;

    printf("Thread #%lx size=%d first=%d\n", GetCurrentThreadId(), end_index - start_index, start_index);

    function_mutex(global_product);

    global_product =  wallisa(start_index, end_index);
    
    printf("Thread #%lx prod=%.20f\n", GetCurrentThreadId(), global_product); 
}

int main(int argc, char** argv) {
     // Sprawdzenie poprawności liczby argumentów wywołania
    if (argc != 3) {
        fprintf(stderr, "\n\t\tERROR\n\tPodaj dwa argumenty: n w\n\tn - liczba wyrazow ciagu  Wallisa\n\tw - liczba watkow\n\n");
        return 1;
    }
    // Pobranie argumentów wywołania i przeparsowanie ich do odpowiednich zmiennych
    const int n = atoi(argv[1]);
    const int w = atoi(argv[2]);

    if (n < 1 || n > MAX_ITERATIONS || w <1 || w > MAX_THREADS) {
        fprintf(stderr, "\n\t\t   ERROR\nArgumenty n i w muszą być liczbami dodatnimi\n\t\tz przedzialu\n\t1<n<1000000000 i 1<w<100\n\n");
        return 1;
    }

    int segmentSize = n / w;
    int remainder = n % w;

    //-------------------------------------------------- w/Threads -------------------------------------------
    // Tworzenie wątków, liczba ich podana przez argument w
    HANDLE threads[w];
    ThreadArgs thread_args[w];
    
    mutex = CreateMutex(NULL, FALSE, NULL);
    // Tworzenie obsługi czasu
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < w; i++) {
        thread_args[i].start_index = i * segmentSize + 1;
        if (i < remainder)
            thread_args[i].start_index += i;
        else 
            thread_args[i].start_index += remainder;
        thread_args[i].end_index = thread_args[i].start_index + segmentSize-1; 
        if (i < remainder) 
            thread_args[i].end_index++;
        threads[i] = CreateThread(NULL, 0, program2pthread, &thread_args[i], 0, NULL ); 
        if(threads[i] == NULL){
            fprintf(stderr, "\n\t\tERROR\n\tNie udało się utworżyc wątku\n\n");
            return 1;
        }         
    }
    WaitForMultipleObjects(w, threads, TRUE, INFINITE);
    double sum = 0;
    for (int i = 0; i < w; i++)
        CloseHandle(threads[i]); 
    CloseHandle(mutex); 

    clock_gettime(CLOCK_REALTIME, &stop);
    double time_product = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)1000000000L;
    printf("w/Thread: PI=%.20f time=%lf\n", global_product, time_product);

    //-------------------------------------------------- wo/Threads -------------------------------------------
    clock_gettime(CLOCK_REALTIME, &start);
    global_product = wallisa(1, n);

    clock_gettime(CLOCK_REALTIME, &stop);
    time_product = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double)1000000000L;
    printf("wo/Thread: PI=%.20f time=%lf\n", global_product, time_product);

    return 0;
}
