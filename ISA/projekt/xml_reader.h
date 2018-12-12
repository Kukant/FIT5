//
// Created by xkukan00 on 09/10/18.
//

#ifndef PROJEKT_ATOM_READER_H
#define PROJEKT_ATOM_READER_H

#include <libxml/tree.h>
#include "arguments.h"

/**
 * Main function for processing XML files. Its main job is to decide which kind of document is to process.
 * @param file the XML file
 * @param args
 * @return
 */
int processXml(std::string file, struct Arguments args);

/**
 * RSS file processing function.
 * @param rss the root element of RSS format
 * @param args
 * @return
 */
int processRSS(xmlNode* rss, struct Arguments args);

/**
 * Atom file processing function
 * @param feed the root element of ATOM format.
 * @param args
 * @return
 */
int processAtom(xmlNode* feed, struct Arguments args);

/**
 * print title of feed / rss
 * @param title
 */
void printTitle(char* title);

#endif //PROJEKT_ATOM_READER_H
