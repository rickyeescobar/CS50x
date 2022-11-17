#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



typedef uint8_t BYTE;

// define block size of 512
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{

    // jpeg filename size definition  (dont forget NUL character)
    char filename[8];


    // create buffer array
    BYTE buffer[512];

    // remember file name
    char *infile = argv[1];

    // make sure user input is correct format
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open raw card file
    FILE *raw_file = fopen(infile, "r");
    // initialize image file
    FILE *img;

    // handle opening file error
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // JPEG counter
    int count = 0;

    // open jpeg flag
    int is_open = 0;

    // initiate loop to read through raw file
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // read 512 bytes into a buffer

        // fread(data, size, number, inptr);
        // fread returns size
        // find when fread != 512 or BYTE_SIZE



        // If start of new JPEG

        // test to find jpg header in buffer
        // jpeg format
        // buffer[0] == 0xff
        // buffer[1] == 0xd8
        // buffer[2] == 0xff
        // (buffer[3] & 0xf0) == 0xe0 ( bitwise arithymitic )


        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {


            // If first JPEG
            if (count == 0)
            {

                // create new JPEG
                // Filenames: ###.jpg, starting at 000.jpg
                // sprintf(filename, "%03i.jpg", ***filename number that you want to sub***);
                // hint : make sure filename has enough memory to fully represent this filename

                sprintf(filename, "%03i.jpg", count);

                // open new image file
                // FILE *img = fopen(filename, "w");
                img = fopen(filename, "w");

                // write to image file
                // fwrite(data, size, number, outptr);
                // fwrite( buffer?, BLOCK_SIZE, number, JPEG file above);
                fwrite(buffer, BLOCK_SIZE, 1, img);

                is_open = 1;

            }

            // Else (if we already found a jpeg)
            else
            {
                //close the file we have been writing to
                // so we can open up new file to write to

                if (is_open == 1)
                {
                    fclose(img);
                    is_open = 0;
                }
                if (is_open == 0)
                {
                    sprintf(filename, "%03i.jpg", count);
                    img = fopen(filename, "w");
                    fwrite(buffer, BLOCK_SIZE, 1, img);
                    is_open = 1;
                }

            }

            // JPEG counter
            count++;
        }

        // Else
        else
        {

            // If already found JPEG , write to new JPEG
            if (count >= 1)
            {
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }

        }
    }

    // Close any remaining files
    fclose(img);
    fclose(raw_file);

}