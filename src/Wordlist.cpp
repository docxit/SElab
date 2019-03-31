#include "DebugInfo.h"
#include "InputParser.h"
#include "WordGraph.h"
#include "readFile.h"
#include "findAllWordList.h"
#include "findAllCharList.h"
#include "DebugTime.h"
#include "WordMost.h"

using namespace std;

#define USAGE " {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]"

int main(int argc, char *argv[]) {
	DebugTime t;

	// parse input
	InputParser inputParser(argv);
	try {
		inputParser.parse();
	} catch (runtime_error err) {
		cerr << err.what() << endl << "Usage: " << argv[0] << USAGE << endl;
		return -1;
	}
	t.printTimeAndRestart("Parse Input");
#ifndef NDEBUG
	cout << endl << "------args information-------" << endl;
	inputParser.print(cout) << endl;
#endif

	// read file
	vector<string> words;
	try {
		readFile(words, inputParser.getInputFileName());
	} catch (runtime_error err) {
		cerr << err.what() << endl;
		return -1;
	}
	t.printTimeAndRestart("Read File");

	// create graph
	WordGraph graph;
	for (const auto &s : words) graph.createArc(s);
	graph.setRevArc();
	t.printTimeAndRestart("Create Graph");
#ifndef NDEBUG
	cout << endl << "------graph information------" << endl;
	graph.print(cout) << endl;
	cout << endl << "--reverse graph information--" << endl;
	graph.printrev(cout) << endl;
#endif

	// calculate
	if (inputParser.getWordNum() != -1) {
#ifndef NDEBUGTIME
		cout << endl << "Detail Time For Calculate: " << endl;
#endif
		if (inputParser.maximumChar())
			findAllCharList(
				graph,
				inputParser.getWordNum(),
				inputParser.getFirstChar(),
				inputParser.getLastChar()
			);
		else findAllWordList(
			graph,
			inputParser.getWordNum(),
			inputParser.getFirstChar(),
			inputParser.getLastChar()
		);
	} else {
		// no word number limit
		WordMost mostSearch(
			graph, 
			inputParser.maximumChar(),
			inputParser.getFirstChar(), 
			inputParser.getLastChar()
		);
		mostSearch.setTimeLimit(2000);
		mostSearch.exec();
		char *ret = (char *)malloc(1000 * sizeof(char));
		ret[0] = '\0';
		for (int i = 0; i < mostSearch.maxQlist.size(); i++)
		{
			strcat(ret, mostSearch.maxQlist[i].value.c_str());
			strcat(ret, "\n");
		}
	}
	t.printTime("\nCalculate Total");
	return 0;
}
