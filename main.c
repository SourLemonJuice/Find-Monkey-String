#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

/* alphabet string */
static char Alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
/* target string */
static char Target_String[] = "hello";
/* something */
static uint8_t Alphabet_Length;
static uint8_t Target_Length;

int main(int argc, char *argv[])
{
    printf("Initing...\n");
    // some length
    Alphabet_Length = strlen(Alphabet);
    Target_Length = strlen(Target_String);
    // Cycle count of main loop
    uint32_t Cycles = 0;
    // Now random index of array Alphabet
    uint8_t Now_Random_Char = 0;
    // Which index of Target_String was detected
    uint8_t Detected_Number = 0;
    // And the max cycles, if you don't want your CPU BOOM
    // Maybe it can be changed later
    uint32_t MAX_Cycles = 4294967295;

    printf("%d\n", argc);
    for (int i = 1; i <= argc - 1; i++)
    {
        puts(argv[i]);
        MAX_Cycles = atoi(argv[i]);
    }

    // return 0;

    while (Cycles < MAX_Cycles)
    {
        /* print */
        Now_Random_Char = rand() % Alphabet_Length;
        putchar(Alphabet[Now_Random_Char]);

        /* detection */
        if (Alphabet[Now_Random_Char] == Target_String[Detected_Number])
            Detected_Number++;
        else
            Detected_Number = 0;

        Cycles++;

        /* if it's the end, break loop. */
        if (Detected_Number == Target_Length)
            break;
    }
    printf("\n%d\n", Cycles);

    /* Meow~ */
    return 0;
}
