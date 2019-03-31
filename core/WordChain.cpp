#include "core.h"
#include"WordMost.h"
#include<iostream>
#include<string.h>
#include<string>

using namespace std;

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail)
{
	WordGraph graph;
	for (int i = 0; i < len; i++)
	{
		graph.createArc(words[i]);
	}
	graph.setRevArc();
	WordMost mostSearch(
		graph,
		false,
		head,
		tail
	);
	mostSearch.setTimeLimit(2000);
	mostSearch.exec();
	for (int i = 0; i < mostSearch.maxQlist.size(); i++)
	{
		result[i] = (char *)malloc(sizeof(char)*mostSearch.maxQlist[i].value.length()*2);
		strcpy(result[i], mostSearch.maxQlist[i].value.c_str());
	}
	return mostSearch.getMaxlength();
}