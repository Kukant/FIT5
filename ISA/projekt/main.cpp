#include <iostream>
#include <vector>
#include <fstream>
#include "arguments.h"
#include "requests.h"
#include "xml_reader.h"

using namespace std;

int processResource(string & url, struct Arguments args) {
    string response = get_response(url, args);

    unsigned long end_of_head = response.find("\r\n\r\n");

    string response_head = response.substr(0, end_of_head + 4);
    string response_body = response.substr(end_of_head + 4);

    if (response.empty() || response_body.empty()) {
        cerr << "Skipping url due to no response: " << url << endl;
        return 1;
    }

    processXml(response_body, args);
};

int main(int argc, char **argv) {
    struct Arguments args = parse_params(argc, argv);

    if (!args.ok) {
        print_help();
        return 1;
    }
    /*printf("ARGS: \n-f %s\n URL: %s, -c %s,-C %s,\n-a %d -u %d -T %d\n",
            args.feedfile.c_str(), args.url.c_str(), args.certfile.c_str(), args.certaddr.c_str(),
            args.show_author, args.show_url, args.show_time);
    printf("ip: %s, port %d, page %s \n", args.ip.c_str(), args.port, args.page.c_str()); */

    vector<string> urls;

    if (args.use_url) {
        urls.emplace_back(args.url);
    } else {
        ifstream feedfile(args.feedfile);

        if(!feedfile.is_open()) {
            perror("Opening feedfile: ");
        }

        string line;
        while(getline(feedfile, line)) {
            if (!line.empty() && line.compare(0, 1, "#") != 0)
                urls.emplace_back(line);
        }
    }

    for (auto &url : urls) {
        processResource(url, args);
        if (&url != &urls.back()){
            cout << endl;
        }
    }

    return 0;
}