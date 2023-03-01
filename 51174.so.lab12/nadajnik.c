// SO IS1 214b LAB12
// Marian Strilets
// sm51174@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("Nieprawidlowa liczba argumentow!\n");
        return -1;
    }

    char *file_key = argv[1];
    char *src_file = argv[2];
    int fd;

    fd = open(file_key, O_CREAT | O_RDWR, 0666);
    if (fd == -1){
        perror("open");
        exit(1);
    }

    // Tworzenie klucza dla funkcji shmget
    key_t key = ftok(file_key, 1);
    if(key == -1) {
        perror("Blad podczas tworzenia klucza");
        return -1;
    }
    // Zapisanie klucza do pliku 
    if (write(fd, &key, sizeof(key_t)) == -1)    {
        perror("write");
        exit(1);
    }
    // Tworzenie segmentu pamieci wspoldzielonej
    int shm_id = shmget(key, 1024, IPC_CREAT | 0666);
    if(shm_id == -1) {
        perror("Blad podczas tworzenia segmentu pamieci wspoldzielonej");
        return -1;
    }

    // Dostep do pamieci wspoldzielonej
    char *shm_ptr = shmat(shm_id, NULL, 0);
    if(shm_ptr == (char *)-1) {
        perror("Blad podczas uzyskiwania dostepu do pamieci wspoldzielonej");
        return -1;
    }

    // Otwieranie pliku zrodlowego
    FILE *src;

    src = fopen(src_file, "r");
    if (src == NULL)
    {
        src = fopen(src_file, "w");
        if (src == NULL)
        {
            perror("Blad podczas otwierania pliku zrodlowego");
            exit(1);
        }
    }


    
    // Wysylanie zawartosci pliku zrodlowego
    int bytes_read;
    //*shm_ptr = '*';
    while((bytes_read = fread(shm_ptr+1, 1, 1024, src)) > 0) {
        //shm_ptr[bytes_read] = '\0';
        
        //// Czekanie na potwierdzenie odbiornika
        while(*shm_ptr != '*') {
            sleep(1);
        }
    
        // Wysylanie danych
        *shm_ptr = '*';
        //fwrite(shm_ptr+1, 1, bytes_read, stdout);
        printf("%s", shm_ptr);
        fprintf(stdout, "Wyslano %d bajtow\n", bytes_read);
    }


    // Zamykanie pliku zrodlowego
    fclose(src);

    // Usuniecie segmentu pamięci współdzielonej
    if(shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Blad podczas usuwania segmentu pamieci wspoldzielonej");
        return -1;
    }

    
    printf("Transfer zakonczony pomyslnie!\n");
    return 0;
}

