#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STRING_LIMIT (0xFFFF / sizeof(char))
#define IS_EQUAL 0

void display_help(const char *bin_exec);
void display_args_limit(const char *bin_exec);
bool is_switch(const char *arg);
int exec_switch(const char *switch_sub_cmd, const char *bin_exec);
void display_wrong_switch();

int main(const int argc, char **argv)
{
    if (argc == 1)
    {
        display_help(argv[0]);
        return EXIT_FAILURE;
    }
    if (argc > 2)
    {
        display_args_limit(argv[0]);
        return EXIT_FAILURE;
    }
    if (is_switch(argv[1]))
    {
        return exec_switch(argv[1], argv[0]);
    }
    char *search_query = (char *)calloc(STRING_LIMIT, sizeof(char)), *token;

    strcat_s(search_query, STRING_LIMIT - 1, "start https://www.google.com/search?q=");
    token = strtok(argv[1], " ");
    while (true)
    {
        strcat_s(search_query, STRING_LIMIT - 1, token);
        token = strtok(NULL, " ");
        if (token == NULL)
        {
            break;
        }
        strcat_s(search_query, STRING_LIMIT - 1, "+");
    }
    system(search_query);
    free(search_query);
    return EXIT_SUCCESS;
}

void display_help(const char *bin_exec)
{
    printf("Command usage: %s \"search query\" or --help to show this.\n", bin_exec);
}

void display_args_limit(const char *bin_exec)
{
    printf("Enclose the query in quotation marks if there are more than one query words.\n");
    display_help(bin_exec);
}

bool is_switch(const char *arg)
{
    int length = strnlen(arg, STRING_LIMIT);

    return ((length >= 2 && arg[0] == '-' && arg[1] == '-')
            || (length >= 1 && arg[0] == '-'));
}

int exec_switch(const char *switch_sub_cmd, const char *bin_exec)
{
    if (strcmp(switch_sub_cmd, "--help") == IS_EQUAL)
    {
        display_help(bin_exec);
        return EXIT_SUCCESS;
    }
    display_wrong_switch();
    return EXIT_FAILURE;
}

void display_wrong_switch()
{
    printf("Invalid switch.\n");
}