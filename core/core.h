#ifndef CORE_H
#define CORE_H

#include "WordGraph.h"

int gen_chain_word(const char* words[], int len, char* result[], char head = '\0', char tail = '\0');

int gen_chain_char(const char* words[], int len, char* result[], char head = '\0', char tail = '\0');

void gen_chain_word_n(const std::vector<std::string> &words, int wordnum, std::vector<std::vector<std::string>> &result, char b = '\0', char e = '\0');

void gen_chain_char_n(const std::vector<std::string> &words, int charnum, std::vector<std::vector<std::string>> &result, char b = '\0', char e = '\0');


#endif // !CORE_H