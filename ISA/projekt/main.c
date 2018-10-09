#include <stdio.h>
#include "arguments.h"

int main(int argc, char **argv) {
    struct Arguments args = parse_params(argc, argv);
    if (!args.ok) {
        print_help();
        return 1;
    }
    printf("ARGS: \n-f %s\n URL: %s, -c %s,-C %s,\n-a %d -u %d -T %d\n",
            args.feedfile, args.url, args.certfile, args.certaddr,
            args.show_author, args.show_url, args.show_time);

    return 0;
}