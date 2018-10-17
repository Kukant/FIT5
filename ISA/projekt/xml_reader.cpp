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

void printArticle(string & title, string & url, string & author, string & time) {
    if (!title.empty()) {
        cout << title << endl;
    }
    if (!url.empty()) {
        cout << "URL: " << url << endl;
    }
    if (!author.empty()) {
        cout << "Autor: " << author << endl;
    }
    if (!time.empty()) {
        cout << "Aktualizace: " << time << endl;
    }
};

void RSSprocessItem(xmlNode* item, struct Arguments args) {
    xmlNode* tmp = nullptr;
    string name;
    string title, url, author, time;
    for (tmp = item->children; tmp; tmp = tmp->next) {
        name = (char *) tmp->name;
        if (name == "title") {
            title = (char *) tmp->children->content;
        } else if (args.show_url && name == "link") {
            url = (char *) tmp->children->content;
        } else if (args.show_author && name == "author") {
            author =  (char *) tmp->children->content;
        } else if (args.show_time && name == "pubDate") {
            time = (char *) tmp->children->content;
        }
    }

    printArticle(title, url, author, time);

    if (args.show_time || args.show_author || args.show_url) {
        cout << endl;
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

string AtomGetLink(xmlNode* link) {
    xmlAttr* tmp = nullptr;
    for (tmp = link->properties; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "href") {
            return (char *)tmp->children->content;
        }
    }

    return "";
}

string AtomGetAuthor(xmlNode* author) {
    xmlNode* tmp = nullptr;
    for (tmp = author->children; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "name" || name == "email") {
            return (char *)tmp->children->content;
        }
    }

    return "";
}

void AtomProcessEntry(xmlNode* entry, struct Arguments args) {
    xmlNode* tmp = nullptr;
    string title, url, author, time;
    for (tmp = entry->children; tmp; tmp = tmp->next) {
        string name((char *) tmp->name);
        if (name == "title") {
            title = (char *)tmp->children->content;
        } else if (args.show_url && name == "link") {
            url = AtomGetLink(tmp);
        } else if (args.show_author && name == "author") {
            author =  AtomGetAuthor(tmp);
        } else if (args.show_time && name == "updated") {
            time = (char *) tmp->children->content;
        }
    }

    printArticle(title, url, author, time);

    if (args.show_time || args.show_author || args.show_url) {
        cout << endl;
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



