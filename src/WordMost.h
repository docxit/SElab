#ifndef WORDMOST_H
#define WORDMOST_H
#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include"WordGraph.h"

class ArcNode;

class ArcNode
{
public:
    std::string value;
    int depth;
};

class WordMost
{
    public:
		WordMost(WordGraph &g, bool charmost, char head, char tail);
        virtual ~WordMost();
		void exec();
        void wordMostSearch();
        void letterMostSearch();
		void setMaxLength(int len) { maxlength = len; }
        int getMaxlength() {return maxlength;}
        void setQlist(std::vector<ArcNode> &qlist) {maxQlist.clear(); maxQlist.assign(qlist.begin(), qlist.end());}
		void wordMostLargeScaleSearch();
		void letterMostLargeScaleSearch();
		void certainHeadSearch(char h);
		void certainHeadSearchLargeScale(char h);
		void letterMostCertainHeadSearch(char a);
		void letterMostCertainHeadSearchLargeScale(char a);
		void setTimeLimit(time_t time) { timelimit = time; }
		void certainTailSearch(char tail);
		void certainTailSearchLargeScale(char tail);
		void letterMostCertainTailSearch(char tail);
		void letterMostCertainTailSearchLargeScale(char tail);
		void printQlist(); 
		void revQlist()
		{
			for (int i = 0; i < maxQlist.size() / 2; i++)
			{
				std::swap(maxQlist[i], maxQlist[maxQlist.size() - 1 - i]);
			}
		}
		WordGraph &getGraph() { return graph; }
        std::vector<ArcNode> maxQlist;
		bool ischarmost;
		char h;
		char t;

    protected:

    private:
		
		time_t timelimit = 1000;
		WordGraph &graph;
        int maxlength = 0;

};

#endif // WORDMOST_H
