//
// Created by zeusko on 09/10/18.
//

#include "arguments.h"

struct Arguments parse_params(int argc, char *argv[]) {
    struct Arguments args;
    args.ok = true;
    args.use_url = true;
    int c;
    while((c = getopt(argc, argv, "f:c:C:auT")) != -1) {
        switch (c) {
            case 'f':
                args.use_url = false;
                args.feedfile.assign(optarg);
                break;
            case 'c':
                args.certfile.assign(optarg);
                break;
            case 'C':
                args.certaddr.assign(optarg);
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
        std::cerr << "Unexpected argument: %s.\n", argv[optind];
        args.ok = false;
        return args;
    }

    if (args.use_url && optind >= argc) {
        std::cerr <<  "Expected URL or feedfile. Nothing given.\n";
        args.ok = false;
        return args;
    } else if (args.use_url && optind < argc){
        args.url = argv[optind];
    }

    if (!args.certfile.empty() && !args.certaddr.empty()) {
        std::cerr <<  "Only -c or only -C can be specified, not both.\n";
        args.ok = false;
        return args;
    }

    if (!args.certfile.empty()) {
        args.cert_location = args.certfile;
    } else if (!args.certaddr.empty()) {
        args.cert_location = args.certaddr;
    }

    parse_url(&args);

    return args;
}

void print_help() {
    std::cerr << "Usage: feedreader <URL | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]" << std::endl;
}

void parse_url(struct Arguments *args) {
    std::string url = args->url;
    args->use_ssl = false;
    args->port = 80;
    args->page =  "/";
    bool success = true;
    char page[STRING_LENGHT] = {0};
    char ip[STRING_LENGHT] = {0};
    if (sscanf(url.c_str(), "http://%99[^:]:%i/%199[^\n]", ip, &args->port, page) == 3) {
    } else if (sscanf(url.c_str(), "http://%99[^/]/%199[^\n]", ip, page) == 2) {
    } else if (sscanf(url.c_str(), "http://%99[^:]:%i[^\n]", ip, &args->port) == 2) {
    } else if (sscanf(url.c_str(), "http://%99[^\n]", ip) == 1) {
    } else if (sscanf(url.c_str(), "https://%99[^:]:%i/%199[^\n]", ip, &args->port, page) == 3) {
        args->use_ssl = true;
    } else if (sscanf(url.c_str(), "https://%99[^/]/%199[^\n]", ip, page) == 2) {
        args->use_ssl = true;
        args->port = 443;
    } else if (sscanf(url.c_str(), "https://%99[^:]:%i[^\n]", ip, &args->port) == 2) {
        args->use_ssl = true;
    } else if (sscanf(url.c_str(), "https://%99[^\n]", ip) == 1) {
        args->use_ssl = true;
        args->port = 443;
    } else {
        success = false;
    }

    args->ip.assign(ip);
    args->page.assign(page);

    if (!success) {
        args->ok = false;
    }
}
