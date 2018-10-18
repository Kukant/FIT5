//
// Created by xkukan00 on 09/10/18.
//

#ifndef PROJEKT_ARGUMENTS_H
#define PROJEKT_ARGUMENTS_H

#include <getopt.h>
#include <string.h>
#include <iostream>

#define STRING_LENGHT 256


/**
 * Struct for storing arguments of program and others.
 */
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

/**
 * Main function for parsing profram arguments
 * @param argc num of args
 * @param argv args
 * @return filled Arguments struct. .ok is true if everything was ok.
 */
struct Arguments parse_params(int argc, char *argv[]);

void print_help();


/**
 * Parsing url.
 * @param args This function only fills url related arguments. ok. is true if url was valid.
 */
void parse_url(struct Arguments *args);

#endif //PROJEKT_ARGUMENTS_H
