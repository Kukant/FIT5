//
// Created by zeusko on 10/10/18.
//

#include <netdb.h>
#include "requests.h"
#include "arguments.h"

BIO *create_connection(char *hostname, in_port_t port) {
    char hostname_port[STRING_LENGHT] = {0};
    sprintf(hostname_port, "%s:%d", hostname, port);
    BIO* bio = BIO_new_connect(hostname_port);
    if(bio == NULL) {
        perror("BIO_new_connect");
        return NULL;
    }

    if(BIO_do_connect(bio) <= 0) {
        perror("BIO_do_connect");
        return NULL;
    }

    return bio;
}
