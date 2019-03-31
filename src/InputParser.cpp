#include "InputParser.h"

using namespace std;

InputParser::InputParser(char *args[]) {
	char **p = args + 1;
	while (*p) {
		this->args.push_back(*p);
		++p;
	}
	this->args.push_back("");
}

void InputParser::parse() {
	for (auto it = args.cbegin(); it != args.cend(); ++it) {
		if (*it == "-w") {
			checkfilename();
			charmost = false;
			filename = *++it;
		} else if (*it == "-c") {
			checkfilename();
			charmost = true;
			filename = *++it;
		} else if (*it == "-h") {
			++it;
			checkcharacter(*it);
			firstchar = tolower((*it)[0]);
		} else if (*it == "-t") {
			++it;
			checkcharacter(*it);
			lastchar = tolower((*it)[0]);
		} else if (*it == "-n") {
			wordnum = atoi((++it)->c_str());
			checknumber(wordnum);
		} else {
			checkarg(*it);
		}
	}
	checknull();
}
