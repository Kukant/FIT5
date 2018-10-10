//
// Created by zeusko on 09/10/18.
//

#include "arguments.h"

struct Arguments parse_params(int argc, char *argv[]) {
    struct Arguments args = {0};
    args.ok = true;
    args.use_url = true;
    int c;
    while((c = getopt(argc, argv, "f:c:C:auT")) != -1) {
        switch (c) {
            case 'f':
                if (strlen(optarg) > STRING_LENGHT - 1) {
                    fprintf(stderr, "feedfile is way too long. ( > %d)\n", STRING_LENGHT);
                    args.ok = false;
                    return args;
                }
                args.use_url = false;
                strcpy(args.feedfile, optarg);
                break;
            case 'c':
                if (strlen(optarg) > STRING_LENGHT - 1) {
                    fprintf(stderr, "certfile is way too long. ( > %d)\n", STRING_LENGHT);
                    args.ok = false;
                    return args;
                }
                strcpy(args.certfile, optarg);
                break;
            case 'C':
                if (strlen(optarg) > STRING_LENGHT - 1) {
                    fprintf(stderr, "certaddr is way too long. ( > %d)\n", STRING_LENGHT);
                    args.ok = false;
                    return args;
                }
                strcpy(args.certaddr, optarg);
                break;
            case 'a':
                args.show_author = true;
                break;
            case 'u':
                args.show_url = true;
                break;
            case 'T':
                args.show_time = true;
                break;

            default:
                args.ok = false;
                return args;
        }
    }

    if (!args.use_url && optind < argc){
        fprintf(stderr, "Unexpected argument: %s.\n", argv[optind]);
        args.ok = false;
        return args;
    }

    if (args.use_url && optind >= argc) {
        fprintf(stderr, "Expected URL or feedfile. Nothing given.\n");
        args.ok = false;
        return args;
    } else if (args.use_url && optind < argc){
        if (strlen(argv[optind]) > STRING_LENGHT - 1) {
            fprintf(stderr, "URL is way too long. ( > %d)\n", STRING_LENGHT);
            args.ok = false;
            return args;
        }
        strcpy(args.url, argv[optind]);
    }

    parse_url(&args);

    return args;
}

void print_help() {
    printf("Usage: feedreader <URL | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]\n");
}

void parse_url(struct Arguments *args) {
    char *url = args->url;
    args->port = 80;
    strcpy(args->page, "/");
    bool success = false;
    if (sscanf(url, "http://%99[^:]:%i/%199[^\n]", args->ip, &args->port, args->page) == 3) {
        success = true;
    } else if (sscanf(url, "http://%99[^/]/%199[^\n]", args->ip, args->page) == 2) {
        success = true;
    } else if (sscanf(url, "http://%99[^:]:%i[^\n]", args->ip, &args->port) == 2) {
        success = true;
    } else if (sscanf(url, "http://%99[^\n]", args->ip) == 1) {
        success = true;
    }

    if (!success) {
        args->ok = false;
    }
}
