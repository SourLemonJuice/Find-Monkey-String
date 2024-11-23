#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "argpx/argpx.h"

#define SELF_NAME "monkey-string"
#ifndef VERSION
    #define VERSION "[Develop Version]"
#endif

enum ExitCode {
    kExitCodeSuccess = EXIT_SUCCESS,
    kExitCodeStdError = EXIT_FAILURE,
    kExitCodeFlagValueInvalid = 10,
    kExitCodeFlagNullValue = 13,
};

static const char kPoolAlphabet[] = "abcdefghijklmnopqrstuvwxyz ";
static const char kPoolFullAlphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
static const char kPoolDigit[] = "0123456789";

struct Config {
    // and the max cycles, if you don't want your CPU BOOM
    // if set to 0, means no limit
    // or, a timer maybe batter?
    uintmax_t max_cycles;
    // TODO use wchar
    char const *sample_pool;
    // whether to print those random char
    bool print_char_bool;
    // whether to print summary
    bool print_summary;
    // target string pointer
    char *target_string;
};

static void ConfigInit(struct Config *conf)
{
    *conf = (struct Config){
        .max_cycles = 0,
        .sample_pool = kPoolAlphabet,
        .print_char_bool = true,
        .print_summary = true,
        .target_string = "cc",
    };
}

static void PrintHelp_(void)
{
    // A help page
    puts("Usage: monkey-string [--help | -h] [--target-string <string>] [--sample-pool <alphabet | full-alphabet | "
         "digit>] [--max-cycles <number uintmax_t>] [--print-stream <true/false>] [--summary <true/false>] "
         "[<target-string>]\n");

    puts("Try to run \"monkey-string hello\" to find word \"hello\". Flag \"--target-string\" will do the same thing.");
    puts("If the target string starts with \"--\" or \"-\", only \"--target-string\" can work.\n");

    puts("By default, characters will output. This will seriously affect the performance.");
    puts("Use \"--print-stream false\" to turn is off.");
    puts("Also can use the \"--summary false\" flag to get a clean char stream.\n");

    puts("And... Don't input any character out of the sample pool(default is lowercase letters and space), program "
         "won't check it.");
}

static void PrintVersion_(void)
{
    printf("Find-Monkey-String %s\n\n", VERSION);

    printf("Published Under MIT License\n");
    printf("Developed by 酸柠檬猹/SourLemonJuice in that 2024\n");
}

static void ParseArguments_(struct Config *conf, int argc, char *argv[])
{
    bool show_help = false;
    bool show_version = false;
    char *pool_name = NULL;

    struct ArgpxStyle arg_style = {0};
    ArgpxAppendGroup(&arg_style, ARGPX_BUILTIN_GROUP_GNU);
    ArgpxAppendGroup(&arg_style, ARGPX_BUILTIN_GROUP_UNIX);

    ArgpxAppendStopSymbol(&arg_style, "--");
    ArgpxAppendStopSymbol(&arg_style, "-");

    // clang-format off

    struct ArgpxFlagSet arg_flag = {0};
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "help",
        .group_idx = 0,
        .action_type = kArgpxActionSetBool,
        .action_load.set_bool = {.target_ptr = &show_help, .source = true},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "h",
        .group_idx = 1,
        .action_type = kArgpxActionSetBool,
        .action_load.set_bool = {.target_ptr = &show_help, .source = true},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "version",
        .group_idx = 0,
        .action_type = kArgpxActionSetBool,
        .action_load.set_bool = {.target_ptr = &show_version, .source = true},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "max-cycles",
        .group_idx = 0,
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarInt, .ptr = &conf->max_cycles},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "target-string",
        .group_idx = 0,
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarString, .ptr = &conf->target_string},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "print-stream",
        .group_idx = 0,
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarBool, .ptr = &conf->print_char_bool},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "summary",
        .group_idx = 0,
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarBool, .ptr = &conf->print_summary},
    });
    ArgpxAppendFlag(&arg_flag, &(struct ArgpxFlagItem){
        .name = "sample-pool",
        .group_idx = 0,
        .action_type = kArgpxActionParamSingle,
        .action_load.param_single = {.type = kArgpxVarString, .ptr = &pool_name},
    });

    struct ArgpxResult *res = ArgpxMain(&(struct ArgpxMainOption){
        .argc = argc,
        .argv = argv,
        .style = &arg_style,
        .flag = &arg_flag,
        .terminate.method = kArgpxTerminateNone,
    });

    // clang-format on

    if (res->status != kArgpxStatusSuccess) {
        printf("%s: arguments error, stop at '%s'\n", SELF_NAME, res->current_argv_ptr);
        printf("ArgParseX: %s\n", ArgpxStatusToString(res->status));
        exit(EXIT_FAILURE);
    }

    if (show_help == true) {
        PrintHelp_();
        exit(EXIT_SUCCESS);
    }

    if (show_version == true) {
        PrintVersion_();
        exit(EXIT_SUCCESS);
    }

    if (pool_name != NULL) {
        if (strcmp(pool_name, "alphabet") == 0) {
            conf->sample_pool = kPoolAlphabet;
        } else if (strcmp(pool_name, "digit") == 0) {
            conf->sample_pool = kPoolDigit;
        } else if (strcmp(pool_name, "full-alphabet") == 0) {
            conf->sample_pool = kPoolFullAlphabet;
        } else {
            printf("%s: invalid sample pool name\n", SELF_NAME);
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    /* Handle CLI options */

    struct Config conf;
    ConfigInit(&conf);
    ParseArguments_(&conf, argc, argv);

    // when all set down
    // get some length
    size_t sample_length = strlen(conf.sample_pool);
    size_t target_length = strlen(conf.target_string);

    /* Main loop block */

    // cycle count of main loop
    uintmax_t cycles = 0;
    // now random index of array alphabet
    size_t now_random_char = 0;
    // which index of target_string was detected
    size_t detected_number = 0;

    while (conf.max_cycles == 0 or cycles < conf.max_cycles) {
        /* get new random char */
        now_random_char = rand() % sample_length;
        /* print? */
        if (conf.print_char_bool == true)
            putchar(conf.sample_pool[now_random_char]);

        /* detection */
        if (conf.sample_pool[now_random_char] == conf.target_string[detected_number])
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
    if (conf.print_char_bool == true)
        printf("\n");

    if (conf.print_summary == true) {
        printf("======== [Summary] ========\n");
        printf("Sample pool:\t\"%s\"\n", conf.sample_pool);
        printf("Target string:\t\"%s\"\n", conf.target_string);
        if (cycles == conf.max_cycles) {
            printf("> The number of cycles may have reached the MAX limit\n");
            printf("Cycle counter:\t%ju\n", cycles);
            printf("Maximum limit:\t%ju\n", conf.max_cycles);
        } else {
            printf("> Task success\n");
            printf("Cycle counter:\t%ju\n", cycles);
        }
    }

    return kExitCodeSuccess;
}
