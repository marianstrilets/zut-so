#include <windows.h>
#include <stdio.h>

#define MEM_SIZE 1000

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s name\n", argv[0]);
        return 1;
    }

    HANDLE MapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,   // read/write access
            FALSE,                 // do not inherit the name
            argv[1]);               // name of mapping object

    if(MapFile == NULL) {
        fprintf(stderr, "Could not open file mapping object\n");
        return 1;
    }

    void *Buf = MapViewOfFile(MapFile, // handle to map object
            FILE_MAP_ALL_ACCESS,  // read/write permission
            0,
            0,
            MEM_SIZE);

    if (Buf == NULL)
    {
        fprintf(stderr, "Could not map view of file\n");
        CloseHandle(MapFile);
        return 2;
    }

    printf("Message: '%s'\n", (char *)Buf);
    if(!UnmapViewOfFile(Buf)) {
        fprintf(stderr, "Could not unmap view of file\n");
        CloseHandle(MapFile);
        return 4;
    }
    CloseHandle(MapFile);
    return 0;
}