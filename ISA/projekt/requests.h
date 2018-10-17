//
// Created by zeusko on 10/10/18.
//

#ifndef PROJEKT_REQUESTS_H
#define PROJEKT_REQUESTS_H
#include <sys/socket.h>
#include <netinet/in.h>

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

#include "arguments.h"
using namespace std;
string get_response(string url, struct Arguments args);

#endif //PROJEKT_REQUESTS_H
