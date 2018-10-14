//
// Created by zeusko on 09/10/18.
//

#ifndef PROJEKT_ARGUMENTS_H
#define PROJEKT_ARGUMENTS_H

#include <getopt.h>
#include <string.h>
#include <iostream>

#define STRING_LENGHT 128

struct Arguments {
    std::string feedfile; // -f
    std::string url; // argument
    bool use_url;
    std::string certfile; // -c
    std::string certaddr; // -C
    std::string cert_location;
    bool show_time; // -T
    bool show_author; // -a
    bool show_url; // -u
    bool ok;
    std::string ip;
    std::string page;
    int port;
    bool use_ssl;
};

struct Arguments parse_params(int argc, char *argv[]);

void print_help();

void parse_url(struct Arguments *args);

#endif //PROJEKT_ARGUMENTS_H
