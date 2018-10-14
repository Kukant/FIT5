//
// Created by zeusko on 14/10/18.
//

#include "atom_reader.h"
#include "libxml/parser.h"
#include "libxml/xmlIO.h"
#include "libxml/xinclude.h"
#include "libxml/tree.h"

using namespace std;
int processAtom(std::string file, struct Arguments args) {
    xmlDocPtr doc = xmlParseDoc((const xmlChar *)file.c_str());
    xmlNode* feed = doc->children;
    xmlNode* current = nullptr;

    if (!feed) {
        cerr << "Feed is not existing, empty XML." << endl;
        return 1;
    }

    for (current = feed->children; current; current = current->next) {
        string name((char *) current->name);
        if (name == "title") {
            cout << "*** " << current->children->content << " ***" << endl;
        } else if (name == "entry") {
            cout << current->children->children->content<< endl;
        }
        //cout << current->name << endl;
    }

    return 0;
}
