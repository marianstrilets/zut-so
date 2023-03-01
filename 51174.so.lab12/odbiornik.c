// SO IS1 214b LAB12
// Marian Strilets
// sm51174@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Nieprawidlowa liczba argumentow!\n");
        return -1;
    }
    char *file_key = argv[1];
    char *dst_file = argv[2];

    // Tworzenie klucza dla funkcji shmget
    key_t key = ftok(file_key, 1);
    if(key == -1){
        perror("Blad podczas tworzenia klucza");
        return -1;
    }

    // Uzyskanie dostepu do pamieci wspoldzielonej
    int shm_id = shmget(key, 1024, 0666);
    if(shm_id == -1){
        perror("Blad podczas uzyskiwania dostepu do pamieci wspoldzielonej");
        return -1;
    }

    char *shm_ptr = shmat(shm_id, NULL, 0);
    if(shm_ptr == (char *)-1){
        perror("Blad podczas uzyskiwania dostepu do pamieci wspoldzielonej");
        return -1;
    }

    // Otwieranie pliku docelowego
    FILE *dst = fopen(dst_file, "r");
    if (dst == NULL)
    {
        dst = fopen(dst_file, "w");
        if (dst == NULL)
        {
            perror("Blad podczas otwierania pliku docelowego");
            exit(1);
        }
    }

    //// Odbieranie danych i zapis do pliku docelowego
    //while(*shm_ptr != '*'){
    //    sleep(1);        
    //}
    while(1){
        // Czekanie na dane od nadajnika
        printf("%s", shm_ptr);
        while(*shm_ptr != '*'){
            sleep(1);
        }
        // Odczytanie danych i zapis do pliku docelowego
        int bytes_received = strlen(shm_ptr + 1);
        fwrite(shm_ptr + 1, 1, bytes_received, dst);
        fprintf(stdout, "Odebrano %d bajtow\n", bytes_received);
        // Potwierdzenie odbioru danych
        *shm_ptr = '\0';
        if(bytes_received < 1024){
            break;
        }
    }

    // Zamykanie pliku docelowego
    fclose(dst);

    // Usunięcie segmentu pamięci współdzielonej
    if(shmctl(shm_id, IPC_RMID, NULL) == -1){
        perror("Blad podczas usuwania segmentu pamieci wspoldzielonej");
        return -1;
    }

    printf("Transfer zakonczony pomyslnie!\n");
    return 0;
}


