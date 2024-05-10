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
static char Target_String[] = "zz";
/* something */
static uint8_t Alphabet_Length;
static uint8_t Target_Length;

int main(int argc, char *argv[])
{
    /* init */
    // Some length
    Alphabet_Length = strlen(Alphabet);
    Target_Length = strlen(Target_String);
    // Cycle count of main loop
    uint32_t Cycles = 0;
    // Now random index of array Alphabet
    uint8_t Now_Random_Char = 0;
    // Which index of Target_String was detected
    uint8_t Detected_Number = 0;
    // And the max cycles, if you don't want your CPU BOOM
    // if set to 0, means no limit
    // or, a timer maybe batter?
    uint32_t MAX_Cycles = 0;

    /* Handle CLI options */
    for (int next_opt_num = 1; next_opt_num <= argc - 1; next_opt_num++)
    {
        /* A help page */
        if (not strcmp(argv[next_opt_num], "help"))
        {
            puts("I don't know...");
            return 0;
        }

        /* Main subcommand */
        // TODO add flags
        if (not strcmp(argv[next_opt_num], "start"))
        {
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                MAX_Cycles = atoi(argv[next_opt_num]);

            continue;
        }

        /* The last one */
        if (next_opt_num = argc - 1)
        {
            puts("Option Error");
            return 1;
        }
    }

    /* Main loop block */
    while (MAX_Cycles == 0 or Cycles < MAX_Cycles)
    {
        /* print */
        Now_Random_Char = rand() % Alphabet_Length;
        putchar(Alphabet[Now_Random_Char]);

        /* detection */
        if (Alphabet[Now_Random_Char] == Target_String[Detected_Number])
            Detected_Number++;
        else
            Detected_Number = 0;

        /* increase cycle counter */
        Cycles++;

        /* if it's the end, break loop. */
        if (Detected_Number == Target_Length)
            break;
    }
    // Break last putchat(), and make a blank line
    printf("\n\n");
    if (Cycles == MAX_Cycles)
        printf("The number of cycles may have reached the max limit. cycles: %d, max limit: %d\n", Cycles, MAX_Cycles);
    else
        printf("It took %d cycles\n", Cycles);

    /* meow~ */
    return 0;
}
