/*
 * COMP15 assignment04, Summer 2020
 * gerp.cpp
 * By: Sean Traynor
 * Completed 
 *
 * The gerp.cpp file will contain a driver function (with a command loop)
 * to index the directory and prompt the user's for queries, which will be
 * executed by an external class.
 */

#include "IndexedDirectory.h"
#include <iostream>    

int main (int argc, char **argv) {
    IndexedDirectory directory(argv[1]);
    std::string query;
    while (query != "@q") {
        std::cout << "Query? ";
        std::cin >> query;
        if (query == "@q") {
            std::cout << "Goodbye! Thank you and have a nice day.\n";
        } else {
            if (query == "@i") {
                std::string word_query;
                std::cin >> word_query;
                directory.caseInsensitiveSearch(word_query);
            } else {
                directory.caseSensitiveSearch(query);
            }
            std::cout << "\n";
        }
    }
    
    return 0;
}