#include "WordGraph.h"

using namespace std;

WordGraph::WordGraph() {
	for (int i = 0; i < 26; i++) {
		v.push_back(Vertex(i + 'a'));
	}
}

void WordGraph::clearAllStar() const {
	for (const auto &vex : v) {
		for (const auto &arc : vex.adjarcs) {
			arc.clearStar();
		}
	}
}

void WordGraph::setRevArc() {
	for (auto &vex : v) {
		for (auto &arc : vex.adjarcs) {
			arc.adjVex().revadjarcs.push_back(&arc);
		}
	}
}

#ifndef NDEBUG
ostream &WordGraph::print(ostream &os) const {
	for (const auto &vex : v) {
		if (!vex.adjarcs.size()) continue;
		os << vex.name << ": " << std::endl;
		for (const auto &arc : vex.adjarcs) {
			os << "\t" << (arc.isStar() ? "(*)" : "") << arc.name;
		}
		os << std::endl;
	}
	return os;
}

ostream &WordGraph::printrev(ostream &os) const {
	for (const auto &vex : v) {
		if (!vex.revadjarcs.size()) continue;
		os << vex.name << ": " << std::endl;
		for (const auto *arc : vex.revadjarcs) {
			os << "\t" << (arc->isStar() ? "(*)" : "") << arc->name;
		}
		os << std::endl;
	}
	return os;
}
#endif // NDEBUG