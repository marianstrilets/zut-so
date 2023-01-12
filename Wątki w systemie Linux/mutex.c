#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* thread_function(void* arg) {
    printf("Wątek: uzyskuję dostęp do zasobu\n");
    pthread_mutex_lock(&mutex);
    printf("Wątek: uzyskałem dostęp do zasobu\n");
    sleep(5);
    pthread_mutex_unlock(&mutex);
    printf("Wątek: zwolniłem dostęp do zasobu\n");
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread, NULL, thread_function, NULL);
    printf("Główny wątek: uzyskuję dostęp do zasobu\n");
    pthread_mutex_lock(&mutex);
    printf("Główny wątek: uzyskałem dostęp do zasobu\n");
    sleep(5);
    pthread_mutex_unlock(&mutex);
    printf("Główny wątek: zwolniłem dostęp do zasobu\n");
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
