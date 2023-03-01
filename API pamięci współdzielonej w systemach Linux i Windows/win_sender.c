#include <windows.h>
#include <stdio.h>

#define MEM_SIZE 1000

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s name message\n", argv[0]);
        return 1;
    }

    HANDLE MapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            MEM_SIZE,                // maximum object size (low-order DWORD)
            argv[1]);                // name of mapping object

    if (MapFile == NULL)
    {
        fprintf(stderr, "Could not create file mapping object\n");
        return 2;
    }
    void *Buf = MapViewOfFile(
            MapFile,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            MEM_SIZE);

    if (Buf == NULL)
    {
        fprintf(stderr, "Could not map view of file\n");
        CloseHandle(MapFile);
        return 3;
    }

    strcpy(Buf, argv[2]);
    puts("Press <Enter> to continue...");
    getch();
    if(!UnmapViewOfFile(Buf)) {
        fprintf(stderr, "Could not unmap view of file\n");
        CloseHandle(MapFile);
        return 4;
    }
    CloseHandle(MapFile);
    return 0;
}