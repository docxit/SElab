#include "core.h"
using namespace std;

static vector<string>::size_type depthLimit;
static vector<string> wordlist;
static char endc;
static vector<vector<string>> *rp;

static inline void writeList() {
	rp->push_back(wordlist);
}

static inline void revWriteList() {
	vector<string> rev;
	for (auto it = wordlist.end(); it != wordlist.begin(); --it) {
		rev.push_back(it[-1]);
	}
	rp->push_back(rev);
}

static void DLS(const Vertex &v) {
	for (const auto &arc : v.adjArcs()) {
		if (arc.isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc.setStar();
				wordlist.push_back(arc.getName());
				DLS(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			} else if (wordlist.size() == depthLimit) {
				wordlist.push_back(arc.getName());
				writeList();
				wordlist.pop_back();
			}
		}
	}
}

static void DLSWithEnd(const Vertex &v) {
	for (const auto &arc : v.adjArcs()) {
		if (arc.isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc.setStar();
				wordlist.push_back(arc.getName());
				DLSWithEnd(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			} else if (wordlist.size() == depthLimit && arc.adjVexName() == endc) {
				wordlist.push_back(arc.getName());
				writeList();
				wordlist.pop_back();
			}
		}
	}
}

static void revDLS(const Vertex &v) {
	for (const auto &arc : v.revAdjArcsPtr()) {
		if (arc->isStar() == false) {
			if (wordlist.size() < depthLimit) {
				arc->setStar();
				wordlist.push_back(arc->getName());
				revDLS(arc->revAdjVex());
				wordlist.pop_back();
				arc->clearStar();
			} else if (wordlist.size() == depthLimit) {
				wordlist.push_back(arc->getName());
				revWriteList();
				wordlist.pop_back();
			}
		}
	}
}

void gen_chain_word_n(const std::vector<std::string> &words, int wordNum, std::vector<std::vector<std::string>> &result, char b, char e) {
	// create graph
	WordGraph graph;
	for (const auto &s : words) graph.createArc(s);
	graph.setRevArc();

	// set global var
	rp = &result;
	depthLimit = wordNum - 1;

	// calculate
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
}
