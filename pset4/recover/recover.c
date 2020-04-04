#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // usage message
    if (argc != 2)
    {
        printf("usage: ./recover image\n");
        return 1;
    }

    //read memory card from command line file name
    FILE *thefile = fopen(argv[1], "r");

    // Declare variables for file length, and fread and fwrite, and define a 'block' using "size_t" type
    size_t file_len;
    size_t blocks_read = 0;
    size_t blocks_written = 0;
    size_t block_size = sizeof(BYTE) * 512;

    // Determine the length of the file in bytes
    fseek(thefile, 0, SEEK_END);
    file_len = ftell(thefile);
    fseek(thefile, 0, SEEK_SET);

    // Determines the number of discrete 512 byte blocks in the file. In this case there's no remainder
    size_t blocks = (file_len - (file_len % 512)) / 512;
    printf("file length: %li bytes \nbyte blocks: %li\nbyte block size: %zu\n", file_len, blocks, block_size);

    // buffer points to a byte
    unsigned char *buffer = NULL;
    // buffer is allocated memory equal to full file length in bytes
    buffer = (unsigned char *) malloc(file_len);

    // filename points to character and allocated 4 bytes of memory
    char *filename = NULL;
    filename = (char *) malloc(4);

    // jpeg counter and other counters
    int num_jpeg = 0;
    long a = 0, b = 0, c = 0;;

    // if file doesn't open returns error
    if (!thefile)
    {
        printf("Unable to open file");
        return 1;
    }

    // Reads entire file into buffer array in 512 byte blocks
    blocks_read = fread(buffer, block_size, blocks, thefile);
    printf("byte blocks read: %zu\n", blocks_read);

    // Checks if array was read correctly
    if (buffer == NULL)
    {
        printf("Memory not allocated to buffer.\n");
        return 1;
    }

    // For each block we check if it starts with jpeg header
    for (int i = 0; i < blocks; i++)
    {
        // b is blocks read to new file, initialised to 0 for each loop
        b = 0;

        // Checks first four characters of the buffer array at block 0
        if (buffer[a] == 0xff && buffer [a + 1] == 0xd8 && buffer[a + 2] == 0xff && (buffer[a + 3] & 0xf0) == 0xe0)
        {
            // if we find a jpeg then increase jpeg count, print the new file name
            num_jpeg++;
            printf("jpeg #%i at chunk %li   ", num_jpeg - 1, a / 512);
            sprintf(filename, "%03i.jpg", num_jpeg - 1);

            // Checks the filename was correctly read in
            if (filename == NULL)
            {
                printf("Memory not allocated to filename.\n");
                return 1;
            }

            // opens a new file with new filename which img points to
            FILE *img = fopen(filename, "w");
            // Writes the first block to the file
            do
            {
                blocks_written = fwrite(&buffer[a], block_size, 1, img);

                // i increases to force the main loop to jump ahead as it is counting in blocks
                // b is blocks read for this file
                // c is total blocks read and does not get reset
                // a is the block count and gets increased, then the condition is checked
                i++;
                b++;
                c++;
                a += 512;
            }
            // while the next block ISN'T a jpeg, and the end of the file hasn't been reached, keep writing!
            while ((!(buffer[a] == 0xff && buffer [a + 1] == 0xd8 && buffer[a + 2] == 0xff && (buffer[a + 3] & 0xf0) == 0xe0))
                   && (file_len - a != 0));

            // once condition has been reached, we close img file and jump to start of loop but at new i position
            printf("blocks in file: %li    total blocks written: %li \n", b, c);
            fclose(img);

        }

        // if jpeg not found check next block
        else
        {
            a += 512;
        }

    }

    // free up the memory allocated to the buffer and filename
    free(buffer);
    free(filename);
}