#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512  // defining block size

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    if (argc < 2)   //ensure that user chooses a file to read
    {
        printf("Usage: ./recover <filename>.raw\n");
        return 1;
    }

    int n_files = 0;    //counter for each jpeg found
    FILE *raw_file = fopen(argv[1], "r");
    char *file_name = malloc(sizeof(char) * 8); //allocate memory for the filename ###.jpg\0. 8 Bytes
    FILE *rec_file = NULL;
    BYTE *buffer = malloc(BLOCK_SIZE); //allocate memory for read buffer
    bool jpg_start = false;     //bool to check if a jpeg was found

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE) //while there are 512 Byte blocks, read them
    {
        //printf("%x  %x  %x  %x \n", buffer[0], buffer[1], buffer[2], buffer[3]);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //look for starting bits of a jpeg
        {
            if (jpg_start)  //if first jpeg bitys found and file has already been written to, close it.
            {
                fclose(rec_file); //was getting still reachable memory on valgrind,
                jpg_start = false;
            }
            jpg_start = true;     //if found starting bits of jpeg, assign new file name, open new file, and increment file counter (for the next file)
            sprintf(file_name, "%03i.jpg", n_files);
            rec_file = fopen(file_name, "w");
            n_files++;
        }
        if (jpg_start)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, rec_file); //start writing after finding the start of jpeg
        }
    }
    free(file_name);
    free(buffer);
    fclose(raw_file);
    fclose(rec_file);
}
