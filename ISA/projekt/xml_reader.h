//
// Created by zeusko on 14/10/18.
//

#ifndef PROJEKT_ATOM_READER_H
#define PROJEKT_ATOM_READER_H

#include <libxml/tree.h>
#include "arguments.h"

int processXml(std::string file, struct Arguments args);
int processRSS(xmlNode* rss, struct Arguments args);
int processAtom(xmlNode* feed, struct Arguments args);
void printTitle(char* title);

#endif //PROJEKT_ATOM_READER_H
