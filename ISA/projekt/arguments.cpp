//
// Created by xkukan00 on 09/10/18.
//

#include "arguments.h"

using namespace std;

struct Arguments parse_params(int argc, char *argv[]) {
    struct Arguments args;
    memset(&args, 0, sizeof(struct Arguments));
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
        cerr << "Unexpected argument:" << argv[optind] << endl;
        args.ok = false;
        return args;
    }

    if (args.use_url && optind >= argc) {
        cerr <<  "Expected URL or feedfile. Nothing given.\n";
        args.ok = false;
        return args;
    } else if (args.use_url && optind < argc){
        args.url = argv[optind];
    }

    if (!args.certfile.empty() && !args.certaddr.empty()) {
        cerr <<  "Only -c or only -C can be specified, not both.\n";
        args.ok = false;
        return args;
    }

    if (!args.certfile.empty()) {
        args.cert_location = args.certfile;
    } else if (!args.certaddr.empty()) {
        args.cert_location = args.certaddr;
    }

    return args;
}

void print_help() {
    cerr << "Usage: feedreader <URL | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]" << endl;
}
