//
// Created by xkukan00 on 09/10/18.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "arguments.h"
#include "requests.h"
#include "xml_reader.h"

#define DEBUG true

using namespace std;

int processResource(string & url, struct Arguments args) {
    string response = get_response(url, args);
    if (response.empty()) {
        cerr << "Skipping url " << url << endl;
        return 1;
    }

    unsigned long end_of_head = response.find("\r\n\r\n");

    string response_head = response.substr(0, end_of_head + 4);
    string response_body = response.substr(end_of_head + 4);

    if (response.empty() || response_body.empty()) {
        cerr << "Skipping url due to no response: " << url << endl;
        return 1;
    }

    processXml(response_body, args);

    return 0;
};

int main(int argc, char **argv) {
    struct Arguments args = parse_params(argc, argv);

    if (!args.ok) {
        print_help();
        return 1;
    }

    if (DEBUG) {
        printf("ARGS: \n-f %s\n URL: %s, -c %s,-C %s,\n-a %d -u %d -T %d use-url %d\n",
               args.feedfile.c_str(), args.url.c_str(), args.certfile.c_str(), args.certaddr.c_str(),
               args.show_author, args.show_url, args.show_time, args.use_url);
        printf("ip: %s, port %d, page %s \n", args.ip.c_str(), args.port, args.page.c_str());
    }

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