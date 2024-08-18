#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum ExitCode {
    kExitCodeSuccess = EXIT_SUCCESS,
    kExitCodeStdError = EXIT_FAILURE,
    kExitCodeFlagValueInvalid = 10,
    kExitCodeFlagNullValue = 13,
};

int main(int argc, char *argv[])
{
    // alphabet
    char Alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
    uint8_t Alphabet_Length;
    // cycle count of main loop
    uint32_t Cycles = 0;
    // now random index of array Alphabet
    uint8_t Now_Random_Char = 0;
    // which index of Target_String was detected
    uint8_t Detected_Number = 0;
    // and the max cycles, if you don't want your CPU BOOM
    // if set to 0, means no limit
    // or, a timer maybe batter?
    uint32_t MAX_Cycles = 0;
    // whether to print those random char
    bool print_char_bool = true;
    // target string pointer
    char *Target_String = "cc";
    uint8_t Target_Length;
    // how many arguments did the program get in processing
    uint8_t Argument_Num = 0;

    srand(time(NULL));

    /* Handle CLI options */
    for (int next_opt_num = 1; next_opt_num <= argc - 1; next_opt_num++) {
        if (strcmp(argv[next_opt_num], "--help") == 0 or strcmp(argv[next_opt_num], "-h") == 0) {
            // A help page
            printf(
                "Usage: monkey-string [--help | -h] [<Target-String>] [--target-string <string>] [--max-cycles <number "
                "uint32_t>] [--printing <ture/false>]\n\n");
            printf("Try to run \"monkey-string hello\" to find word \"hello\". Flag --target-string will do the same "
                   "thing.\n");
            printf("If the target string starts with \"--\" or \"-\", only --target-string can work.\n\n");
            printf("By default, characters will output. This will seriously affect the performance.\n");
            printf("Use \"--printing false\" to turn is off.\n\n");
            printf("And... Don't input any character out of the lowercase and space, program won't check it.\n\n");
            printf("Published Under MIT License\n");
            printf("By 酸柠檬猹/SourLemonJuice 2024\n");
            return 0;
        } else if (strcmp(argv[next_opt_num], "--max-cycles") == 0) {
            // set maximum cycles
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                MAX_Cycles = atoi(argv[next_opt_num]);
            else
                goto ERROR_flag_null_value;
            continue;
        } else if (strcmp(argv[next_opt_num], "--target-string") == 0) {
            // target string
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                Target_String = argv[next_opt_num];
            else
                goto ERROR_flag_null_value;
            continue;
        } else if (strcmp(argv[next_opt_num], "--printing") == 0) {
            // control whether to print random characters
            next_opt_num++;
            if (next_opt_num <= argc - 1) {
                if (strcmp(argv[next_opt_num], "true") == 0)
                    print_char_bool = true;
                else if (strcmp(argv[next_opt_num], "false") == 0)
                    print_char_bool = false;
                else
                    goto ERROR_invalid_value;
            } else
                goto ERROR_flag_null_value;
            continue;
        } else if (strncmp(argv[next_opt_num], "--", 2) == 0 or strncmp(argv[next_opt_num], "-", 1) == 0) {
            printf("Invalid flag: \"%s\"\n", argv[next_opt_num]);
            return kExitCodeStdError;
        }

        if (Argument_Num >= 1) {
            Argument_Num++;
            printf("Too many arguments: \"%s\"\n", argv[next_opt_num]);
            return kExitCodeStdError;
        } else if (Argument_Num == 0) {
            Argument_Num++;
            // the first argument same like "--target-string"
            Target_String = argv[next_opt_num];
            continue;
        }
    }

    // when all setted down
    // get some length
    Alphabet_Length = strlen(Alphabet);
    Target_Length = strlen(Target_String);
    /* Main loop block */
    while (MAX_Cycles == 0 or Cycles < MAX_Cycles) {
        /* get new random char */
        Now_Random_Char = rand() % Alphabet_Length;
        /* print? */
        if (print_char_bool == true)
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
    if (print_char_bool == true)
        printf("\n");
    printf("======== [Summary] ========\n");
    printf("The target string is \"%s\"\n", Target_String);
    if (Cycles == MAX_Cycles) {
        printf("The number of cycles may have reached the MAX limit.\n");
        printf("Cycles: %d, Max Limit: %d\n", Cycles, MAX_Cycles);
    } else {
        printf("Task Success\n");
        printf("It took %d cycles\n", Cycles);
    }
    return kExitCodeSuccess;

/* meow~ */
ERROR_invalid_value:
    puts("some value is invalid");
    return kExitCodeFlagValueInvalid;
ERROR_flag_null_value:
    puts("A CLI flag don't have its value");
    return kExitCodeFlagNullValue;
}
