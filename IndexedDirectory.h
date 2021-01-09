/*
 * COMP15 assignment04, Summer 2020
 * IndexedDirectory.h
 * By: Sean Traynor
 * Completed 8/5/20
 *
 * IndexedDirectory Class Implentation
 * Purpose: The IndexedDirectory Class will hold all of the information from
 *          all of the files in the given directory. This class will be
 *          implemented using three vectors: one that holds all the file paths
 *          within the given directory, one that holds all of the lines in the
 *          files, and one that holds all of the words in the files. The Class
 *          will interact with all three when searching for words, both in the
 *          case insensitive and standard cases.
 */

#ifndef INDEXEDDIRECTORY_H
#define INDEXEDDIRECTORY_H

#include <vector>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <iostream>

typedef std::string line;
typedef std::vector<line> file;

typedef std::string word;
typedef std::unordered_set<word> word_line;
typedef std::vector<word_line> word_file;


class IndexedDirectory {
public:
    
    // Constructor
    IndexedDirectory(std::string directory_name);
    
    // Public Member Functions
    void caseSensitiveSearch(std::string word);
    void caseInsensitiveSearch(std::string word);
    
private:
    
    void indexFiles();
    file readInFileLines(std::string curr_file_path);
    bool searchThroughFile(std::string word, int file_num);
    word_file readInFileWords(std::string curr_file_path);
    word_line readInLineWords(std::string curr_line);
    
    void printLineAndPath(int file_num, int line_num);
    
    std::string stripNonAlphaNum(std::string s);
    std::string toLowercase(std::string s);
    std::string toUpperCase(std::string s);
    std::string capatalizeFirstLetter(std::string s);
    
    
    std::string directory_name;
    int num_files;
    
    std::vector<file> file_list;
    std::vector<word_file> word_file_list;
    std::vector<std::string> file_paths;
    
};

#endif