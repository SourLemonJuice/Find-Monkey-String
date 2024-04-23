#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* alphabet string */
static char Alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
/* target string */
static char Target_String[] = "hello";
/* something */
static uint8_t Alphabet_Length;
static uint8_t Target_Length;

int main(void)
{
    printf("Initing...\n");
    // some length
    Alphabet_Length = strlen(Alphabet);
    Target_Length = strlen(Target_String);
    // Cycle count of main loop
    uint8_t Cycles = 0;
    // Now random index of array Alphabet
    uint8_t Now_Random_Char = 0;
    // Which index of Target_String was detected
    uint8_t Detected_Number = 0;
    // And the max cycles, if you don't want your CPU BOOM
    // Maybe it can be changed later
    uint16_t MAX_Cycles = 1000;

    do
    {
        /* print */
        Now_Random_Char = rand() % Alphabet_Length;
        putchar(Alphabet[Now_Random_Char]);

        /* detection */
        if (Alphabet[Now_Random_Char] == Target_String[Detected_Number])
            Detected_Number++;
        else
            Detected_Number = 0;

        /* if it's the end, break loop. */
        if (Detected_Number == Target_Length)
            break;

        Cycles++;
    } while (Cycles <= MAX_Cycles);
    printf("\n");

    /* Meow~ */
    return 0;
}
