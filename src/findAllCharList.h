#ifndef FIND_ALL_CHAR_LIST_H
#define FIND_ALL_CHAR_LIST_H

#include "DebugInfo.h"
#include "WordGraph.h"
#include "DebugTime.h"

void findAllCharList(const WordGraph &, int, char, char);

#endif // FIND_ALL_CHAR_LIST_H
int gen_chain_word_n(const std::vector<std::string> &words, int len, char head, char tail, std::vector<std::string> &result);
