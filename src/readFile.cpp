#include "readFile.h"
#include <iostream>
#include <algorithm>

void readFile(std::vector <std::string> &words, const std::string &path) {
	bool rst = false;
	std::ifstream in(path.c_str());
	if (!in.is_open()) throw std::runtime_error("Open " + path + " failed");
	int c;
	bool flag = true;
	std::string buffer;
	while ((c = in.get()) != EOF) {
		if (isalpha(c)) {
			buffer += tolower(c);
			flag = true;
			rst = true;
		} else if (flag) {
			if (!rst) continue;
			//if(find(words.begin(), words.end(), buffer))
				words.push_back(buffer);
			buffer = "";
			flag = false;
		}
	}
	if (words.size() == 0) throw std::runtime_error("No words!");
	//ШЅжи
	std::vector <std::string>::iterator iter = unique(words.begin(), words.end());
	words.erase(iter, words.end());
}


