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
static char Target_String_Default[] = "cc";
/* something */
static uint8_t Alphabet_Length;
static uint8_t Target_Length;

int main(int argc, char *argv[])
{
    // TODO SO UGLY Here. move them to a structure please
    /* init */
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
    // whether to print the char(random)
    bool print_char_bool = true;
    // target string pointer
    char *Target_String = Target_String_Default;

    /* Handle CLI options */
    for (int next_opt_num = 1; next_opt_num <= argc - 1; next_opt_num++)
    {
        // A help page
        if(not strcmp(argv[next_opt_num], "--help"))
        {
            puts("I don't know...");
            puts("--help | --max_cycles <number uint32_t> | --target_string <string> | --print_char <ture/false : default ture>");
            goto APP_exit;
        }
        // set maximum cycles
        if(not strcmp(argv[next_opt_num], "--max_cycles"))
        {
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                MAX_Cycles = atoi(argv[next_opt_num]);
            else
                goto ERROR_flag_null_value;
            continue;
        }
        // target string
        if(not strcmp(argv[next_opt_num], "--target_string"))
        {
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                Target_String = argv[next_opt_num];
            else
                goto ERROR_flag_null_value;
            continue;
        }
        // control whether to print random characters
        if(not strcmp(argv[next_opt_num], "--print_char"))
        {
            next_opt_num++;
            if (next_opt_num <= argc - 1)
            {
                if(not strcmp(argv[next_opt_num], "true"))
                    print_char_bool = true;
                else if(not strcmp(argv[next_opt_num], "false"))
                    print_char_bool = false;
                else
                    goto ERROR_invalid_value;
            }
            else
                goto ERROR_flag_null_value;
            continue;
        }

        /* for invalid flags */
        if (next_opt_num = argc - 1)
        {
            puts("Flag invalid");
            goto ERROR_normal;
        }
    }

    // when ALL setted DOWN
    // get some length
    Alphabet_Length = strlen(Alphabet);
    Target_Length = strlen(Target_String);
    /* Main loop block */
    while (MAX_Cycles == 0 or Cycles < MAX_Cycles)
    {
        /* get new random char */
        Now_Random_Char = rand() % Alphabet_Length;
        /* print? */
        if(print_char_bool)
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
    // Break last putchat(), and make a dividing line
    printf("\n");
    puts("======[Summary]======");
    if (Cycles == MAX_Cycles)
    {
        printf("WARNING: The number of cycles may have reached the MAX limit.\n");
        printf("Cycles: %d, Max Limit: %d\n", Cycles, MAX_Cycles);
    }
    else
    {
        printf("Task Done\n");
        printf("It took %d cycles\n", Cycles);
    }

    /* meow~ */
    // TODO use enum
    APP_exit:
    return 0;
    ERROR_normal:
    return 1;
    ERROR_invalid_value:
    puts("some value is invalid");
    return 10;
    ERROR_flag_null_value:
    puts("A CLI flag don't have its value");
    return 13;
}
