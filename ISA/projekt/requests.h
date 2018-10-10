//
// Created by zeusko on 10/10/18.
//

#ifndef PROJEKT_REQUESTS_H
#define PROJEKT_REQUESTS_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <openssl/bio.h>

BIO *create_connection(char *hostname, in_port_t port);
#endif //PROJEKT_REQUESTS_H
