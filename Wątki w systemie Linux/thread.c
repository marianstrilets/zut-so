#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

    // Wątek 1
void* thread1_function(void* arg) {
    printf("Wątek 1\n");
    return NULL;
}

    // Wątek 2
void* thread2_function(void* arg) {
    printf("Wątek 2\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

/*
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
            thread - wskaźnik do zmiennej typu pthread_t, w której zostanie zapisany identyfikator nowego wątku
            attr - wskaźnik do struktury zawierającej atrybuty wątku, może być ustawiony na NULL
            start_routine - wskaźnik do funkcji, która będzie wywoływana jako wątek
            arg - argument przekazywany do funkcji start_routine
        Funkcja pthread_join() służy do oczekiwania na zakończenie wątku. Jej składnia wygląda następująco:
*/
    // Tworzenie wątku 1
    pthread_create(&thread1, NULL, thread1_function, NULL);

    // Tworzenie wątku 2
    pthread_create(&thread2, NULL, thread2_function, NULL);

    // Czekanie na zakończenie wątku 1
    pthread_join(thread1, NULL);

    // Czekanie na zakończenie wątku 2
    pthread_join(thread2, NULL);

    return 0;
}
