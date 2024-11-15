#include <ctype.h>
#include <inttypes.h>
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

static const char kPoolAlphabet[] = "abcdefghijklmnopqrstuvwxyz ";
static const char kPoolFullAlphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
static const char kPoolDigit[] = "0123456789";

int main(int argc, char *argv[])
{
    // TODO use wchar
    char const *sample_pool = kPoolAlphabet;

    size_t sample_length;
    // cycle count of main loop
    uintmax_t cycles = 0;
    // now random index of array alphabet
    size_t now_random_char = 0;
    // which index of target_string was detected
    size_t detected_number = 0;
    // and the max cycles, if you don't want your CPU BOOM
    // if set to 0, means no limit
    // or, a timer maybe batter?
    uintmax_t max_cycles = 0;
    // whether to print those random char
    bool print_char_bool = true;
    // whether to print summary
    bool print_summary = true;
    // target string pointer
    char *target_string = "cc";
    size_t target_length;
    // how many arguments did the program get in processing
    int argument_num = 0;

    srand(time(NULL));

    /* Handle CLI options */
    // TODO CHANGE THOSE SHIT!!!!
    for (int next_opt_num = 1; next_opt_num <= argc - 1; next_opt_num++) {
        if (strcmp(argv[next_opt_num], "--help") == 0 or strcmp(argv[next_opt_num], "-h") == 0) {
            // A help page
            puts("Usage: monkey-string [--help | -h] [--target-string <string>] [--sample-pool <alphabet | "
                 "full-alphabet | digit>] [--max-cycles <number uintmax_t>] [--print-stream <true/false>] [--summary "
                 "<true/false>] [<target-string>]\n");

            puts("Try to run \"monkey-string hello\" to find word \"hello\". Flag \"--target-string\" will do the same "
                 "thing.");
            puts("If the target string starts with \"--\" or \"-\", only \"--target-string\" can work.\n");

            puts("By default, characters will output. This will seriously affect the performance.");
            puts("Use \"--print-stream false\" to turn is off.");
            puts("Also can use the \"--summary false\" flag to get a clean char stream.\n");

            puts("And... Don't input any character out of the sample pool(default is lowercase letters and space), "
                 "program won't check it.\n");

            puts("Published Under MIT License");
            puts("By 酸柠檬猹/SourLemonJuice 2024");
            return 0;
        } else if (strcmp(argv[next_opt_num], "--max-cycles") == 0) {
            // set maximum cycles
            next_opt_num++;
            if (next_opt_num <= argc - 1) {
                char *temp_endstr;
                max_cycles = strtoumax(argv[next_opt_num], &temp_endstr, 10);
                if (temp_endstr[0] != '\0') {
                    perror("Flag value of --max-cycles was invalid(may not be a number)");
                    exit(kExitCodeFlagValueInvalid);
                }
            } else {
                goto ERROR_flag_null_value;
            }
            continue;
        } else if (strcmp(argv[next_opt_num], "--target-string") == 0) {
            // target string
            next_opt_num++;
            if (next_opt_num <= argc - 1)
                target_string = argv[next_opt_num];
            else
                goto ERROR_flag_null_value;
            continue;
        } else if (strcmp(argv[next_opt_num], "--print-stream") == 0) {
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
        } else if (strcmp(argv[next_opt_num], "--summary") == 0) {
            // whether to show the summary
            next_opt_num++;
            if (next_opt_num <= argc - 1) {
                if (strcmp(argv[next_opt_num], "true") == 0)
                    print_summary = true;
                else if (strcmp(argv[next_opt_num], "false") == 0)
                    print_summary = false;
                else
                    goto ERROR_invalid_value;
            } else
                goto ERROR_flag_null_value;
            continue;
        } else if (strcmp(argv[next_opt_num], "--sample-pool") == 0) {
            next_opt_num++;
            if (next_opt_num <= argc - 1) {
                if (strcmp(argv[next_opt_num], "alphabet") == 0)
                    sample_pool = kPoolAlphabet;
                else if (strcmp(argv[next_opt_num], "digit") == 0)
                    sample_pool = kPoolDigit;
                else if (strcmp(argv[next_opt_num], "full-alphabet") == 0)
                    sample_pool = kPoolFullAlphabet;
                else
                    goto ERROR_invalid_value;
            } else
                goto ERROR_flag_null_value;
            continue;
        } else if (strncmp(argv[next_opt_num], "--", 2) == 0 or strncmp(argv[next_opt_num], "-", 1) == 0) {
            printf("Invalid flag: \"%s\"\n", argv[next_opt_num]);
            return kExitCodeStdError;
        }

        if (argument_num >= 1) {
            argument_num++;
            printf("Too many arguments: \"%s\"\n", argv[next_opt_num]);
            return kExitCodeStdError;
        } else if (argument_num == 0) {
            argument_num++;
            // the first argument same like "--target-string"
            target_string = argv[next_opt_num];
            continue;
        }
    }

    // when all set down
    // get some length
    sample_length = strlen(sample_pool);
    target_length = strlen(target_string);
    /* Main loop block */
    while (max_cycles == 0 or cycles < max_cycles) {
        /* get new random char */
        now_random_char = rand() % sample_length;
        /* print? */
        if (print_char_bool == true)
            putchar(sample_pool[now_random_char]);

        /* detection */
        if (sample_pool[now_random_char] == target_string[detected_number])
            detected_number++;
        else
            detected_number = 0;

        /* increase cycle counter */
        cycles++;

        /* if it's the end, break loop. */
        if (detected_number == target_length)
            break;
    }
    // Break last putchat(), and make a dividing line
    if (print_char_bool == true)
        printf("\n");

    if (print_summary == true) {
        printf("======== [Summary] ========\n");
        printf("Sample pool:\t\"%s\"\n", sample_pool);
        printf("Target string:\t\"%s\"\n", target_string);
        if (cycles == max_cycles) {
            printf("> The number of cycles may have reached the MAX limit\n");
            printf("Cycle counter:\t%ju\n", cycles);
            printf("Maximum limit:\t%ju\n", max_cycles);
        } else {
            printf("> Task success\n");
            printf("Cycle counter:\t%ju\n", cycles);
        }
    }

    return kExitCodeSuccess;

/* meow~ */
// Maybe we shouldn't use them in future
ERROR_invalid_value:
    puts("some value is invalid");
    return kExitCodeFlagValueInvalid;
ERROR_flag_null_value:
    puts("A CLI flag don't have its value");
    return kExitCodeFlagNullValue;
}
