#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <exception>
#include "DebugInfo.h"

class InputParser {
private:
	std::vector<std::string> args;	// end with ""
	std::string filename;
	bool charmost = false;
	char firstchar = '\0';
	char lastchar = '\0';
	int wordnum = -1;

	void checkfilename() {
		if (filename.size()) {
			throw std::runtime_error("too much input file");
		}
	}

	void checkcharacter(const std::string &s) {
		if (s.size() != 1 || !isalpha(s[0])) {
			throw std::runtime_error("'" + s + "' not a valid character");
		}
	}

	void checknumber(int num) {
		if (num <= 0) {
			throw std::runtime_error("word number should be a positive integer");
		}
	}

	void checkarg(const std::string &s) {
		if (s.size()) {
			throw std::runtime_error("unknown arg '" + s + "'");
		}
	}

	void checknull() {
		if (!filename.size()) {
			throw std::runtime_error("no input file");
		}
	}

public:
	InputParser(char *args[]);
	void parse();
	const std::string &getInputFileName() { return filename; }
	bool maximumChar() { return charmost; }
	char getFirstChar() { return firstchar; }	// '\0' by default
	char getLastChar() { return lastchar; }		// '\0' by default
	int getWordNum() { return wordnum; }		// -1 by default

#ifndef NDEBUG
	std::ostream &print(std::ostream &os = std::cout) {
		os << "input file: " << filename << std::endl
			<< "maximum: " << (charmost ? "character" : "word") << std::endl
			<< "first character: " << firstchar << std::endl
			<< "last character: " << lastchar << std::endl
			<< "word number: " << wordnum << std::endl;
		return os;
	}
#endif	// NDEBUG
};

#endif	// INPUT_PARSER_H