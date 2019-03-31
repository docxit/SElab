#include "findAllWordList.h"
#include "DebugInfo.h"

using namespace std;
#define OUTPUT_FILE "solution.txt"
static vector<const string *>::size_type depthLimit;
static vector<const string *> wordlist;
static FILE *fp;
static int num = 0;
static char endc;

static DebugTime t_writefile;

static inline void openFile() {
	if ((fp = fopen(OUTPUT_FILE, "w")) == NULL) {
		cerr << "error: cannot open file 'solution.txt'" << endl;
		exit(0);
	}
	fprintf(fp, "           \n");
}

static inline void closeFile() {
	rewind(fp);
	fprintf(fp, "%d", num);
	fclose(fp);
}

static inline void writeListToFile(const char *s) {	// s is the last string 
	t_writefile.continueAfterPause();
	++num;
	for (const auto *s : wordlist) {
		fprintf(fp, "%s\n", s->c_str());
	}
	fprintf(fp, "%s\n\n", s);
	t_writefile.pause();
}

static inline void revWriteListToFile(const char *s) {	// s is the first string 
	t_writefile.continueAfterPause();
	++num;
	fprintf(fp, "%s\n", s);
	for (auto it = wordlist.cend(); it != wordlist.cbegin(); --it) {
		fprintf(fp, "%s\n", (*(it - 1))->c_str());
	}
	fprintf(fp, "\n");
	t_writefile.pause();
}

static void DLS(const Vertex &v) {
	for (const auto &arc : v.adjArcs()) {
		if (arc.isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc.setStar();
				wordlist.push_back(&arc.getName());
				DLS(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			} else if (wordlist.size() == depthLimit) {
				writeListToFile(arc.getName().c_str());
			}
		}
	}
}

static void DLSWithEnd(const Vertex &v) {
	for (const auto &arc : v.adjArcs()) {
		if (arc.isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc.setStar();
				wordlist.push_back(&arc.getName());
				DLSWithEnd(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			} else if (wordlist.size() == depthLimit && arc.adjVexName() == endc) {
				writeListToFile(arc.getName().c_str());
			}
		}
	}
}

static void revDLS(const Vertex &v) {
	for (const auto &arc : v.revAdjArcsPtr()) {
		if (arc->isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc->setStar();
				wordlist.push_back(&arc->getName());
				revDLS(arc->revAdjVex());
				wordlist.pop_back();
				arc->clearStar();
			} else if (wordlist.size() == depthLimit) {
				revWriteListToFile(arc->getName().c_str());
			}
		}
	}
}

void findAllWordList(const WordGraph &graph, int wordnum, char b, char e) {

	DebugTime t;
	openFile();
	depthLimit = wordnum - 1;
	t.printTimeAndRestart("\tOpen File And Preprocessing");

	t_writefile.restartAndPause();
	if (b == '\0' && e == '\0') {
		for (const auto &v : graph.getAllVertex()) 
			DLS(v);
	} else if (b && e == '\0') {
		DLS(graph.getVertex(b));
	} else if (b == '\0' && e) {
		revDLS(graph.getVertex(e));
	} else {
		endc = e;
		DLSWithEnd(graph.getVertex(b));
	}
	t.printTimeAndRestart("\tDLS", cout, t_writefile.getSeconds());
	t_writefile.printTime("\tWrite File");

	closeFile();
	t.printTime("\tClose File");
}
