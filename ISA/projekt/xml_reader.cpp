//
// Created by zeusko on 14/10/18.
//

#include "xml_reader.h"
#include "libxml/parser.h"
#include "libxml/xmlIO.h"
#include "libxml/xinclude.h"
#include "libxml/tree.h"

using namespace std;
int processXml(std::string file, struct Arguments args) {
    xmlDocPtr doc = xmlParseDoc((const xmlChar *)file.c_str());
    xmlNode* feed = nullptr;
    xmlNode* rss = nullptr;
    string feed_name = "feed";
    string rss_name = "rss";

    xmlNode* tmp = nullptr;
    for (tmp = doc->children; feed_name != (char *)tmp->name &&
                              rss_name != (char *)tmp->name &&
                              tmp; tmp = tmp->next );

    if (!tmp) {
        cerr << "XML is not valid RSS or ATOM format" << endl;
        return -1;
    } else if (feed_name == (char *)tmp->name) {
        feed = tmp;
    } else {
        rss = tmp;
    }

    if (feed) {
        processAtom(feed, args);
    } else {
        processRSS(rss, args);
    }

    return 0;
}

void RSSprocessItem(xmlNode* item, struct Arguments args) {
    xmlNode* tmp = nullptr;
    string name;
    for (tmp = item->children; tmp; tmp = tmp->next) {
        name = (char *) tmp->name;
        if (name == "title") {
            cout << tmp->children->content << endl;
        } else if (args.show_url && name == "link") {
            cout << "URL: " << tmp->children->content << endl;
        }
    }
}

void RSSprocessChannel(xmlNode* channel, struct Arguments args){
    xmlNode* tmp = nullptr;
    string name;
    for (tmp = channel->children; tmp; tmp = tmp->next) {
        name = (char *) tmp->name;
        if (name == "title") {
            printTitle((char *)tmp->children->content);
        } else if (name == "item") {
            RSSprocessItem(tmp, args);
        }
    }
}

int processRSS(xmlNode* rss, struct Arguments args) {
    xmlNode* tmp = nullptr;
    for (tmp = rss->children; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "channel") {
            RSSprocessChannel(tmp, args);
        }
    }

    return 0;
}

void AtomProcessLink(xmlNode* link) {
    xmlAttr* tmp = nullptr;
    for (tmp = link->properties; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "href") {
            cout << "URL: " << (char *)tmp->children->content << endl;
            return;
        }
    }
}

void AtomProcessEntry(xmlNode* entry, struct Arguments args) {
    xmlNode* tmp = nullptr;
    for (tmp = entry->children; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "title") {
            cout << (char *)tmp->children->content << endl;
        } else if (args.show_url && name == "link") {
            AtomProcessLink(tmp);
        }
    }
}

int processAtom(xmlNode* feed, struct Arguments args) {
    xmlNode* tmp = nullptr;
    for (tmp = feed->children; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "title") {
            printTitle((char *)tmp->children->content);
        } else if (name == "entry") {
            AtomProcessEntry(tmp, args);
        }
    }
}

void printTitle(char* title) {
    cout << "*** " << title << " ***" << endl;
}
