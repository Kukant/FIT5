//
// Created by zeusko on 10/10/18.
//

#include <netdb.h>
#include "requests.h"



std::string get_response(std::string &request, struct Arguments args) {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    BIO* bio = nullptr;
    SSL_CTX* ctx = nullptr;
    SSL* ssl;
    std::string hostname_port = args.ip + ":" + std::to_string(args.port);

    if (args.use_ssl) {
        ctx = SSL_CTX_new(SSLv23_client_method());
        if (!args.cert_location.empty()) {
            if(!SSL_CTX_load_verify_locations(ctx, args.cert_location.c_str(), nullptr)) {
                std::cerr << "Could not load verify locations.\n" << std::endl;
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
        std::cerr << "BIO create connection";
        return "";
    }

    if (BIO_do_connect(bio) <= 0) {
        std::cerr << "Error: " << ERR_reason_error_string(ERR_get_error()) << std::endl;
        std::cerr << ERR_error_string(ERR_get_error(), nullptr)<< std::endl;
        return "";
    }

    char buffer[STRING_LENGHT] = {0};
    std::string response;
    if(BIO_write(bio, request.c_str(), (int) request.length()) <= 0) {
        if(! BIO_should_retry(bio)) {
            std::cerr << "Error: " << ERR_reason_error_string(ERR_get_error()) << std::endl;
            std::cerr << ERR_error_string(ERR_get_error(), nullptr)<< std::endl;
        }
    }

    while(BIO_read(bio, buffer, STRING_LENGHT - 1) != 0){
        response += buffer;
        bzero(buffer, STRING_LENGHT);
    }

    BIO_free_all(bio);
    if (ctx != nullptr)
        SSL_CTX_free(ctx);

    return response;
}