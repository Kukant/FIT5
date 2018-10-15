#include <iostream>
#include "arguments.h"
#include "requests.h"
#include "xml_reader.h"

int main(int argc, char **argv) {

    struct Arguments args = parse_params(argc, argv);

    if (!args.ok) {
        print_help();
        return 1;
    }
    printf("ARGS: \n-f %s\n URL: %s, -c %s,-C %s,\n-a %d -u %d -T %d\n",
            args.feedfile.c_str(), args.url.c_str(), args.certfile.c_str(), args.certaddr.c_str(),
            args.show_author, args.show_url, args.show_time);
    printf("ip: %s, port %d, page %s \n", args.ip.c_str(), args.port, args.page.c_str());


    std::string request = "GET /"+ args.page +" HTTP/1.0\r\n"
                          "Host: "+ args.ip +"\r\n"
                          "Connection: close\r\n"
                          "User-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\n"
                          "\r\n";

    std::string response = get_response(request, args);

    if (response.empty()) {
        std::cerr << "No response from server" << std::endl;
        return 1;
    }

    unsigned long end_of_head = response.find("\r\n\r\n");

    std::string response_head = response.substr(0, end_of_head + 4);
    std::string response_body = response.substr(end_of_head + 4);

    processXml(response_body, args);

    //std::cout << "Response: \n" << response;

    return 0;
}