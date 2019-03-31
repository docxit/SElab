#ifndef WORD_GRAPH_H
#define WORD_GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include "DebugInfo.h"

class Arc;
class Vertex;
class WordGraph;

class Arc {
	friend class WordGraph;
private:
	std::string name;
	Vertex &adjv;
	Vertex &revAdjv;
	mutable bool star = false;

public:
	Arc(const std::string &s, Vertex &v, Vertex &revv) : name(s), adjv(v), revAdjv(revv) {}
	std::string::size_type getLength() const { return name.size(); }
	const std::string &getName() const { return name; }
	char adjVexName() const { return name[name.size() - 1]; }	// arc head
	char revAdjVexName() const { return name[0]; }	// arc tail
	Vertex &adjVex() const { return adjv; }	// arc head
	Vertex &revAdjVex() const { return revAdjv; }	// arc tail
	void setStar() const { star = true; }
	void clearStar() const { star = false; }
	bool isStar() const { return star; }
};


class Vertex {
	friend class WordGraph;
private:
	char name;
	std::vector<Arc> adjarcs;
	std::vector<Arc *> revadjarcs;
public:
	explicit Vertex(char n) : name(n) {}
	char getName() const { return name; }
	const std::vector<Arc> &adjArcs() const { return adjarcs; }
	std::vector<Arc> &adjArcs() { return adjarcs; }
	const std::vector<Arc *> &revAdjArcsPtr() const { return revadjarcs; }
	std::vector<Arc *> &revAdjArcsPtr() { return revadjarcs; }
};


class WordGraph {
	friend class WordMost;

private:
	std::vector<Vertex> v;
	
public:
	WordGraph();
	Vertex &getVertex(char c) { return v[c - 'a']; }
	const Vertex &getVertex(char c) const { return v[c - 'a']; }
	void setRevArc();
	void clearAllStar() const;
	std::vector<Vertex> &getAllVertex() { return v; }
	const std::vector<Vertex> &getAllVertex() const { return v; }
	void createArc(const std::string &s) {
		const char b = s[0], e = s[s.size() - 1];
		getVertex(b).adjarcs.push_back(Arc(s, getVertex(e), getVertex(b)));
	}
#ifndef NDEBUG
	std::ostream &print(std::ostream &os = std::cout) const;
	std::ostream &printrev(std::ostream &os = std::cout) const;
#endif	// NDEBUG

};

#endif	// WORD_GRAPH_H