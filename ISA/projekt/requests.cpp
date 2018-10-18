//
// Created by xkukan00 on 09/10/18.
//

#include <netdb.h>
#include "requests.h"


using namespace std;

string get_response(string url, struct Arguments args) {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    BIO* bio = nullptr;
    SSL_CTX* ctx = nullptr;
    SSL* ssl;

    struct Arguments url_args;
    url_args.ok = true;
    url_args.url.assign(url);
    parse_url(&url_args);
    if (!url_args.ok) {
        cerr << "Could not parse url: " << url << endl;
        return "";
    }

    string request = "GET /"+ url_args.page +" HTTP/1.0\r\n"
                     "Host: "+ url_args.ip +"\r\n"
                     "Connection: close\r\n"
                     "User-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\n"
                     "\r\n";

    string hostname_port = url_args.ip + ":" + to_string(url_args.port);

    if (url_args.use_ssl) {
        ctx = SSL_CTX_new(SSLv23_client_method());
        if (!args.cert_location.empty()) {
            if(!SSL_CTX_load_verify_locations(ctx, args.cert_location.c_str(), nullptr)) {
                cerr << "Could not verify certificate of server " << url_args.ip << "." << endl;
                return "";
            }
        } else {
            SSL_CTX_set_default_verify_paths(ctx);
        }

        bio = BIO_new_ssl_connect(ctx);
        BIO_set_conn_hostname(bio, hostname_port.c_str());
        BIO_get_ssl(bio, & ssl);
        SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    } else {
        bio = BIO_new_connect(hostname_port.c_str());
    }

    if (!bio) {
        cerr << "BIO create connection" << endl;
        return "";
    }

    if (BIO_do_connect(bio) <= 0) {
        cerr << "Error: " << ERR_reason_error_string(ERR_get_error()) << endl;
        cerr << ERR_error_string(ERR_get_error(), nullptr)<< endl;
        return "";
    }

    char buffer[STRING_LENGHT] = {0};
    string response;
    if(BIO_write(bio, request.c_str(), (int) request.length()) <= 0) {
        if(! BIO_should_retry(bio)) {
            cerr << "Error: " << ERR_reason_error_string(ERR_get_error()) << endl;
            cerr << ERR_error_string(ERR_get_error(), nullptr)<< endl;
        }
    }

    while(BIO_read(bio, buffer, STRING_LENGHT - 1) != 0){
        response += buffer;
        bzero(buffer, STRING_LENGHT);
    }

    BIO_free_all(bio);
    if (ctx != nullptr)
        SSL_CTX_free(ctx);

    if (response.empty()) {
        cerr << "No response from server" << endl;
        return "";
    }

    return response;
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