/*
 * COMP15 assignment04, Summer 2020
 * IndexedDirectory.cpp
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

#include "IndexedDirectory.h"
#include "index_dir.h"
#include <iostream>

/*
 * IndexedDirectory Constructor
 * Purpose:      Creates an IndexedDirectory Object
 * Arguments:    The name of the directory to index
 * Return:       None
 * Effects:      - Sets the private member variable file_paths equal to the
 *               return from the index_dir function in the index_dir.h file
 *               - Calls the indexFiles function, which indexes all of the
 *               files within the specified directory
 * Notes:        All the files are fully indexed once the constructor returns
 */
IndexedDirectory::IndexedDirectory(std::string directory_name) {
    this->directory_name = directory_name;
    this->file_paths = index_dir(this->directory_name);
    this->num_files = this->file_paths.size();
    indexFiles();
};

/*
 * caseSensitiveSearch
 * Purpose:      Runs the case sensitive query
 * Arguments:    The word to search for throughout the directory
 * Return:       None
 * Effects:      Calls the searchThroughFile function for each file in the
 *               directory
 * Notes:        - Strips the non-alphanumeric characters in the word before
 *               searching through the directory
 *               - Counts the number of times the word is found in the
 *               directory -- if that number is 0, print the 'not found'
 *               statement
 *               
 */
void IndexedDirectory::caseSensitiveSearch(std::string word) {
    std::string word_to_search = stripNonAlphaNum(word);
    
    int num_found = 0;
    bool word_found;
    for (int i = 0; i < num_files; i++) {
        word_found = searchThroughFile(word_to_search, i);
        if (word_found) num_found++;
    }
    
    if (num_found == 0) {
        std::cout << word_to_search << " Not Found. ";
        std::cout << "Try case insensitive search with @i.\n";
    }
};

/*
 * caseInsensitiveSearch
 * Purpose:      Runs the case insensitive search query
 * Arguments:    The word to search for throughout the directory
 * Return:       None
 * Effects:      Calls the searchThroughFile function for each file in the
 *               directory
 * Notes:        - Strips the non-alphanumeric characters in the word before
 *               searching through the directory
 *               - Creates three versions of the word to search for: all
 *               lowercase, all uppercase, and the first letter capitalized
 *               - Counts the number of times the word is found in the
 *               directory -- if that number is 0, print the 'not found'
 *               statement
 */
void IndexedDirectory::caseInsensitiveSearch(std::string word) {
    std::string word_to_search = stripNonAlphaNum(word);
    std::string word_to_search_lc = toLowercase(word_to_search);
    std::string word_to_search_uc = toUpperCase(word_to_search);
    std::string word_to_search_c = capatalizeFirstLetter(word_to_search);
    
    int num_found = 0;
    bool word_found;
    for (int i = 0; i < num_files; i++) {
        word_found = searchThroughFile(word_to_search_lc, i);
        if (word_found) num_found++;
        
        word_found = searchThroughFile(word_to_search_uc, i);
        if (word_found) num_found++;
        
        if (word_to_search.length() > 1) {
            word_found = searchThroughFile(word_to_search_c, i);
            if (word_found) num_found++;
        }
    }
    
    if (num_found == 0) std::cout << word_to_search_lc << " Not Found.\n";
};

/*
 * searchThroughFile
 * Purpose:      Searches through a single file for the specified word
 * Arguments:    1. The word to search for throughout the directory
 *               2. The index of the file in the file_paths vector
 * Return:       Whether or not the word is found in the file (bool)
 * Effects:      - If the word is found, the printLineAndPath function is
 *               called, which prints the line and path where the word is found
 * Notes:        
 */
bool IndexedDirectory::searchThroughFile(std::string word, int file_num) {
    int num_lines = this->word_file_list[file_num].size();
    word_line curr_line;
    bool word_found = false;
    for (int i = 0; i < num_lines; i++) {
        curr_line = this->word_file_list[file_num][i];
        if (curr_line.find(word) != curr_line.end()) {
            printLineAndPath(file_num, i);
            word_found = true;
        }
    }
    return word_found;
};

/*
 * printLineAndPath
 * Purpose:      Prints the correctly formatted file path, line number, and the
 *               line where the word is found
 * Arguments:    1. The index of the file in the file_paths vector
 *               2. The line number where the word was found
 * Return:       None
 * Effects:      None
 * Notes:        - The line number is 1 less than the actual line number
 *               because it is derived from a vector, which starts at 0 instead
 *               of 1 (i.e. line 1 would be represented by index 0)
 */
void IndexedDirectory::printLineAndPath(int file_num, int line_num) {
    std::cout << this->file_paths[file_num] << ":" << line_num + 1 << ": ";
    std::cout << this->file_list[file_num][line_num] << "\n";
};

/*
 * stripNonAlphaNum
 * Purpose:      Strips any non-alphanumeric characters from the beginning or
 *               end of the specified word
 * Arguments:    The word to strip from
 * Return:       The new word without non-alphanumeric characters
 * Effects:      None
 * Notes:        Uses the STL isalnum function
 */
std::string IndexedDirectory::stripNonAlphaNum(std::string s) {
    char curr_letter;
    std::string new_word = "";

    int i, j;
    
    // Iterates through the beginning
    for (i = 0; i < s.length(); i++) {
        curr_letter = s[i];
        if (isalnum(curr_letter)) break;
    }
    
    // Iterates through the end
    for (j = s.length() - 1; j >= 0; j--) {
        curr_letter = s[j];
        if (isalnum(curr_letter)) break;
    }
    
    // Add all of the characters to the string to return
    for (int l = i; l <= j; l++) {
        new_word += s[l];
    }

    return new_word;
};

/*
 * toLowercase
 * Purpose:      Takes in a string and turns all of the letters into lowercase
 * Arguments:    The string to change
 * Return:       The new string, with all lowercase letters
 * Effects:      None
 * Notes:        Assumes all characters are alphanumeric (no effect on numbers)
 */
std::string IndexedDirectory::toLowercase(std::string s) {
    int string_length = s.length();
    std::string new_word = "";
    
    char curr_letter;
    for (int i = 0; i < string_length; i++) {
        curr_letter = s[i];
        if (curr_letter > 64 && curr_letter < 91) curr_letter += 32;
        new_word += curr_letter;
    }
    
    return new_word;
};

/*
 * toUpperCase
 * Purpose:      Takes in a string and turns all of the letters into uppercase
 * Arguments:    The string to change
 * Return:       The new string, with all uppercase letters
 * Effects:      None
 * Notes:        Assumes all characters are alphanumeric (no effect on numbers)
 */
std::string IndexedDirectory::toUpperCase(std::string s) {
    int string_length = s.length();
    std::string new_word = "";
    
    char curr_letter;
    for (int i = 0; i < string_length; i++) {
        curr_letter = s[i];
        if (curr_letter > 96 && curr_letter < 123) curr_letter -= 32;
        new_word += curr_letter;
    }
    
    return new_word;
};

/*
 * toUpperCase
 * Purpose:      Takes in a string and turns all of the letters into uppercase
 * Arguments:    The string to change
 * Return:       The new string, with all uppercase letters
 * Effects:      None
 * Notes:        Makes all of the characters lowercase, then capitalizes the
 *               first letter
 */
std::string IndexedDirectory::capatalizeFirstLetter(std::string s) {
    int string_length = s.length();
    s = toLowercase(s);
    std::string new_word = "";
    
    char curr_letter = s[0];
    curr_letter -= 32;
    new_word += curr_letter;
    for (int i = 1; i < string_length; i++) {
        curr_letter = s[i];
        new_word += curr_letter;
    }
    
    return new_word;
};

/*
 * indexFiles
 * Purpose:      Indexes all of the files in the directory and stores data in
 *               this instance of the IndexedDirectory Object
 * Arguments:    None
 * Return:       None
 * Effects:      - Adds all of the lines and words of the files into the
 *               private member variables
 * Notes:        Calls both the readInFileLines and readInFileWords functions
 *               to help read in the files into the data structure
 */
void IndexedDirectory::indexFiles() {
    std::string curr_file_path;
    for (int i = 0; i < this->num_files; i++) {
        curr_file_path = this->file_paths[i];
        this->file_list.push_back(readInFileLines(curr_file_path));
        this->word_file_list.push_back(readInFileWords(curr_file_path));
    }
};

/*
 * readInFileLines
 * Purpose:      Reads in the lines from the file and puts it into a 'file'
 *               type, which is a vector of 'line' (string)
 * Arguments:    The file path of the current file to read in
 * Return:       The 'file' of lines in the current file
 * Effects:      None
 * Notes:        Uses a filestream and a stringstream to read in the lines
 */
file IndexedDirectory::readInFileLines(std::string curr_file_path) {
    line curr_line;
    file curr_file;
    std::ifstream infile(curr_file_path.c_str());
    std::stringstream line_stream;
    
    while (getline(infile, curr_line)) {
        line_stream.str(curr_line);
        curr_file.push_back(curr_line);
        line_stream.clear();
    }
    
    return curr_file;
};

/*
 * readInFileWords
 * Purpose:      Reads in the words from the file and puts it into a
 *               'word_file', which is a vector of 'word_line', which is an
 *               unordered_set of 'word' (string)
 * Arguments:    The file path of the current file to read in
 * Return:       The 'word_file' of lines in the current file
 * Effects:      None
 * Notes:        Calls the readInLineWords function to get the words in each
 *               individual line in the file
 */
word_file IndexedDirectory::readInFileWords(std::string curr_file_path) {
    word_file curr_word_file;
    line curr_line;
    std::ifstream infile(curr_file_path.c_str());
    word_line curr_word_line;
    
    while (getline(infile, curr_line)) {
        curr_word_line = readInLineWords(curr_line);
        curr_word_file.push_back(curr_word_line);
    }
    
    return curr_word_file;
};

/*
 * readInLineWords
 * Purpose:      Reads in the words from a line in a file
 * Arguments:    The current line to extract the words from
 * Return:       The 'word_line' of words from the current line
 * Effects:      None
 * Notes:        Strips any non-alphanumeric characters from the words to make
 *               searching must more seamless
 */
word_line IndexedDirectory::readInLineWords(std::string curr_line) {
    word curr_word;
    word_file curr_word_file;
    std::stringstream line_stream;
    word_line curr_word_line;
    
    line_stream.str(curr_line);
    line_stream >> curr_word;
    while (!line_stream.fail()) {
        curr_word = stripNonAlphaNum(curr_word);
        curr_word_line.insert(curr_word);
        line_stream >> curr_word;
    }
    
    return curr_word_line;
};