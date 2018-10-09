//
// Created by zeusko on 09/10/18.
//

#ifndef PROJEKT_ARGUMENTS_H
#define PROJEKT_ARGUMENTS_H

#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#define STRING_LENGHT 128

struct Arguments {
    char feedfile[STRING_LENGHT]; // -f
    char url[STRING_LENGHT]; // argument
    bool use_url;
    char certfile[STRING_LENGHT]; // -c
    char certaddr[STRING_LENGHT]; // -C
    bool show_time; // -T
    bool show_author; // -a
    bool show_url; // -u
    bool ok;
};

struct Arguments parse_params(int argc, char *argv[]);

void print_help();

#endif //PROJEKT_ARGUMENTS_H
