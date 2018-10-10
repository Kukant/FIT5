#include <stdio.h>
#include "arguments.h"
#include "requests.h"

int main(int argc, char **argv) {
    struct Arguments args = parse_params(argc, argv);
    if (!args.ok) {
        print_help();
        return 1;
    }
    printf("ARGS: \n-f %s\n URL: %s, -c %s,-C %s,\n-a %d -u %d -T %d\n",
            args.feedfile, args.url, args.certfile, args.certaddr,
            args.show_author, args.show_url, args.show_time);
    printf("ip: %s, port %d, page %s \n", args.ip, args.port, args.page);

    BIO* bio = create_connection(args.ip, (in_port_t) 80);
    if (!bio)
        return 1;

    char buffer[STRING_LENGHT] = {0};
    char request[STRING_LENGHT] = {0};
    
    sprintf(request, "GET /%s HTTP/1.1\r\n"
                    "Host: %s\r\n"
                    "Connection: close, User-Agent\r\n"
                    "\r\n", args.page, args.ip);

    if(BIO_write(bio, request, (int)strlen(request)) <= 0) {
        if(! BIO_should_retry(bio)) {
            perror("write");
        }
    }

    while(BIO_read(bio, buffer, STRING_LENGHT - 1) != 0){
        printf("%s", buffer);
        bzero(buffer, STRING_LENGHT);
    }

    BIO_free_all(bio);

    return 0;
}