//
// Created by xkukan00 on 09/10/18.
//

#ifndef PROJEKT_REQUESTS_H
#define PROJEKT_REQUESTS_H
#include <sys/socket.h>
#include <netinet/in.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "arguments.h"
using namespace std;

/**
 * Gets HTTP response.
 * @param url Url to request
 * @param args other useful arguments
 * @return empty string in case of eroor or empty response, else response
 */
string get_response(string url, struct Arguments args);

#endif //PROJEKT_REQUESTS_H
