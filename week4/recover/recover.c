#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong Command line interface argument, Please enter only the name of the jpeg you want to recover\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File pointer NULL\n");
        return 1;
    }

    int jpg_num = 0;
    char fname[8]; // Contains the characters ["#', "#', "#', ".", "j", "p", "g"] so always 8 chars.

    BYTE data_arr[512]; // Buffer
    FILE *jpg = NULL; // Instantialize it before the loop so that undeclared indentifier doesnt occur.

    while (fread(data_arr, sizeof(BYTE), 512, file) == 512) // Read 512 bytes(block) every loop into data_arr, and only loop if there really are atleast 512 bytes left to read in the file.
    {
        if (data_arr[0] == 0xff && data_arr[1] == 0xd8 && data_arr[2] == 0xff && data_arr[3] >= 224 && data_arr[3] <= 238) // Check if the first 4 bytes in a block are jpeg signatures.
        {
            if (jpg_num > 0) // If an image file already exists than jpg_num will be greater than 0, and before reassigning the variable name to point at a diffrent address(file), we need to close the previous one.
            {
                fclose(jpg);
            }
            sprintf(fname, "%03i.jpg", jpg_num); // Assign(prints a formatted string into an area in memory) the name of the file "###.jpg" to the char array fname. %03i makes it so the number has a width of 3 and is padded with zeroes so that when jpg_num = 0 the output is 000 and when jpg_num = 12 the output is 012.
            jpg = fopen(fname, "w"); // jpg was already instantialized as a pointer to a file, now creating and assigning it to point at the address of a file with the current fname with the ability to write into it.
            if (file == NULL) // If file was not read properly(not enough memory maybe idk)
            {
                printf("Image file pointer NULL\n");
                return 3;
            }
            jpg_num += 1; // If a jpg signature was found and a file was created, increment the amount of jpgs in order for the next file to have the proper name.
        }
        if (jpg_num > 0) // If jpg_num is zero than no jpgs were found and data would be written to the address NULL, which would cause a segmentation error.
        {
            fwrite(data_arr, sizeof(BYTE), 512, jpg);
        }
    }
    fclose(jpg); // Close the last found jpg image file.
    fclose(file); // Close the card.raw file.
    return 0;
}