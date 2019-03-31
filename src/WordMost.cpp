#include "WordMost.h"

using namespace std;

WordMost::WordMost(WordGraph &g, bool charmost, char head, char tail) :graph(g)
{
	ischarmost = charmost;
	h = head;
	t = tail;
}

void WordMost::exec()
{
	cout << ischarmost << endl;
	int wordnum = 0;
	for (int i = 0; i < 26; i++)
	{
		wordnum += (int)graph.v[i].adjArcs().size();
	}
	if (ischarmost == false)
	{
		if (h != '\0')
		{
			ofstream ofh("solution.txt");
			if (wordnum <= 50)
				certainHeadSearch(h);
			else
				certainHeadSearchLargeScale(h);
			
			ofh << "word most search: " << "head = " << h << " (" << wordnum << ")" << endl;
			ofh << "word most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
		if (t != '\0')
		{
			if (wordnum <= 50)
				certainTailSearch(t);
			else
				certainTailSearchLargeScale(t);
			ofstream ofh("solution.txt");
			ofh << "word most search: " << "tail = " << t << " (" << wordnum << ")" << endl;
			ofh << "word most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
		if (h == '\0' && t == '\0')
		{
			if (wordnum <= 50)
				wordMostSearch();
			else
				wordMostLargeScaleSearch();
			ofstream ofh("solution.txt");
			ofh << "word most search: " << "(" << wordnum << ")" << endl;
			ofh << "word most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
	}
	else
	{
		if (h != '\0')
		{
			if (wordnum <= 50)
				letterMostCertainHeadSearch(h);
			else
				letterMostCertainHeadSearchLargeScale(h);
			ofstream ofh("solution.txt");
			ofh << "letter most search: " << "head = " << h << " (" << wordnum << ")" << endl;
			ofh << "letter most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
		if (t != '\0')
		{
			if (wordnum <= 50)
				letterMostCertainTailSearch(t);
			else
				letterMostCertainTailSearchLargeScale(t);
			ofstream ofh("solution.txt");
			ofh << "letter most search: " << "tail = " << t << " (" << wordnum << ")" << endl;
			ofh << "letter most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
		if (h == '\0'&&t == '\0')
		{
			if (wordnum <= 50)
				letterMostSearch();
			else
				letterMostLargeScaleSearch();
			ofstream ofh("solution.txt");
			ofh << "letter most search: " << " (" << wordnum << ")" << endl;
			ofh << "letter most list length = " << getMaxlength() << endl;
			for (int i = 0; i < maxQlist.size(); i++)
				ofh << maxQlist[i].value << " ";
			ofh << endl;
			ofh.close();
			return;
		}
	}
}

WordMost::~WordMost()
{
    //dtor
}

void WordMost::printQlist()
{
	for (int i = 0; i < maxQlist.size(); i++)
		std::cout << maxQlist[i].value << " ";
	cout << endl;
}

void DSearch(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
{
    int flag = 0;
    for(int i=0; i<vex.adjArcs().size(); i++)
    {
        if(vex.adjArcs()[i].isStar() == false)
        {
            /*cout << vex.adjArcs()[i].getName() << endl;*/
            flag = 1;
            vex.adjArcs()[i].setStar();
            node.depth = depth;
            node.value = vex.adjArcs()[i].getName();
            qlist.push_back(node);
            DSearch(qlist, depth+1, vex.adjArcs()[i].adjVex() , node, wm);
            vex.adjArcs()[i].clearStar();
            qlist.pop_back();
            /*for(int i=0; i<qlist.size() ; i++)
                cout << qlist[i].value << " ";
            cout << endl;*/
        }
    }
    if(flag == 0)
    {
		/*for (int i = 0; i < qlist.size(); i++)
			cout << qlist[i].value << " ";
		cout << endl;*/
        if(depth-1 > wm->getMaxlength())
        {
            wm->setMaxLength(depth-1);
            wm->setQlist(qlist);
        }
    }
}

void DSearch2(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
{
    int flag = 0;
    for(int i=0; i<vex.adjArcs().size(); i++)
    {
        if(vex.adjArcs()[i].isStar() == false)
        {
            /*cout << vex.adjArcs()[i].getName() << endl;*/
            flag = 1;
            vex.adjArcs()[i].setStar();
            node.depth = depth;
            node.value = vex.adjArcs()[i].getName();
            qlist.push_back(node);
            DSearch2(qlist, depth+(int)node.value.length(), vex.adjArcs()[i].adjVex() , node, wm);
            vex.adjArcs()[i].clearStar();
            qlist.pop_back();
            /*for(int i=0; i<qlist.size() ; i++)
                cout << qlist[i].value << qlist.size() << " ";
            cout << endl;*/
        }
    }
    if(flag == 0)
    {
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
        if(depth > wm->getMaxlength())
        {
            wm->setMaxLength(depth);
            wm->setQlist(qlist);
        }
    }
}

void revDSearch2(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
{
	int flag = 0;
	for (int i = 0; i < vex.revAdjArcsPtr().size(); i++)
	{
		if (vex.revAdjArcsPtr()[i]->isStar() == false)
		{
			/*cout << vex.adjArcs()[i].getName() << endl;*/
			flag = 1;
			vex.revAdjArcsPtr()[i]->setStar();
			node.depth = depth;
			node.value = vex.revAdjArcsPtr()[i]->getName();
			qlist.push_back(node);
			revDSearch2(qlist, depth + (int)node.value.length(), vex.revAdjArcsPtr()[i]->revAdjVex(), node, wm);
			vex.revAdjArcsPtr()[i]->clearStar();
			qlist.pop_back();
			/*for(int i=0; i<qlist.size() ; i++)
				cout << qlist[i].value << qlist.size() << " ";
			cout << endl;*/
		}
	}
	if (flag == 0)
	{
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
		if (depth > wm->getMaxlength())
		{
			wm->setMaxLength(depth);
			wm->setQlist(qlist);
			wm->revQlist();
		}
	}
}

void WordMost::certainHeadSearch(char a)
{
	setMaxLength(-1);
	graph.clearAllStar();
	vector<ArcNode> qlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	DSearch(qlist, 1, v[a-'a'], node, this);
	graph.clearAllStar();
}

void WordMost::wordMostSearch()
{
    setMaxLength(-1);
    graph.clearAllStar();
    vector<ArcNode> qlist;
    ArcNode node;
    vector<Vertex> &v = graph.v;
    for(int i=0; i<26; i++)
    {
        DSearch(qlist, 1, v[i], node, this);
		graph.clearAllStar();
    }
}

void WordMost::letterMostSearch()
{
    setMaxLength(-1);
    graph.clearAllStar();
    vector<ArcNode> qlist;
    ArcNode node;
    vector<Vertex> &v = graph.v;
    for(int i=0; i<26; i++)
    {
        DSearch2(qlist, 0, v[i], node, this);
		graph.clearAllStar();
    }
}

void WordMost::letterMostCertainHeadSearch(char a)
{
	setMaxLength(-1);
	graph.clearAllStar();
	vector<ArcNode> qlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	DSearch2(qlist, 0, v[a-'a'], node, this);
	graph.clearAllStar();
	
}

void randDSearch(vector<Arc *> &arclist,vector<ArcNode> &qlist, Vertex &vex, ArcNode &node)
{
	vector<int> arcArray;
	for (int i = 0; i < vex.adjArcs().size(); i++)
	{
		if (vex.adjArcs()[i].isStar() == false)
		{
			arcArray.push_back(i);
		}
	}
	/*cout <<"vex " << vex.getName() << " " <<  " arcArray = " << arcArray.size() << endl;*/
	if (arcArray.size() == 0)
	{
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
		return;
	}
	else
	{
		int rnum = rand() % arcArray.size();
		vex.adjArcs()[arcArray[rnum]].setStar();
		arclist.push_back(&vex.adjArcs()[arcArray[rnum]]);
		node.value = vex.adjArcs()[arcArray[rnum]].getName();
		qlist.push_back(node);
		randDSearch(arclist, qlist, vex.adjArcs()[arcArray[rnum]].adjVex(), node);
	}
}

void WordMost::certainHeadSearchLargeScale(char a)
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist, lastarclist;
	vector<ArcNode> qlist, lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(), lasttime = clock();
	int vexnum;
	int arcnum;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = a-'a';
			randDSearch(arclist, qlist, v[vexnum], node);
			curlength = qlist.size();
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit / 50)
		{
			if (curlength > 20)
				arcnum = curlength - rand() % 10 - 1;
			else if (curlength == 1)
				arcnum = 0;
			else
				arcnum = curlength - rand() % (curlength / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			Arc *removearc = arclist[arcnum];
			for (int j = arcnum; j < curlength; j++)
			{
				arclist[j]->clearStar();
			}
			arclist.erase(begin(arclist) + arcnum, end(arclist));

			randDSearch(arclist, qlist, removearc->revAdjVex(), node);
			if (qlist.size() > curlength)
			{
				curlength = qlist.size();
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
		}
	}

}

void WordMost::wordMostLargeScaleSearch()
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist,lastarclist;
	vector<ArcNode> qlist,lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(),lasttime = clock();
	int vexnum;
	int arcnum;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = rand() % 26;
			randDSearch(arclist, qlist, v[vexnum], node);
			curlength = qlist.size();
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit/50)
		{
			if (curlength > 20)
				arcnum = curlength - rand() % 10 - 1;
			else if (curlength == 1)
				arcnum = 0;
			else
				arcnum = curlength - rand() % (curlength / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			Arc *removearc = arclist[arcnum];
			for (int j = arcnum; j < curlength; j++)
			{
				arclist[j]->clearStar();
			}
			arclist.erase(begin(arclist) + arcnum, end(arclist));
	
			randDSearch(arclist, qlist, removearc->revAdjVex(), node);
			if (qlist.size() > curlength)
			{
				curlength = qlist.size();
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
		}
	}

}

void WordMost::letterMostLargeScaleSearch()
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist, lastarclist;
	vector<ArcNode> qlist, lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(), lasttime = clock();
	int vexnum;
	int arcnum;
	int len;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = rand() % 26;
			randDSearch(arclist, qlist, v[vexnum], node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			curlength = len;
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit / 50)
		{
			if (qlist.size() == 1)
				arcnum = 0;
			else
				arcnum = qlist.size() - rand() % (qlist.size() / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			for (int j = arcnum; j < arclist.size(); j++)
			{
				arclist[j]->clearStar();
			}
			Arc *removearc = arclist[arcnum];
			arclist.erase(begin(arclist) + arcnum, end(arclist));

			randDSearch(arclist, qlist, removearc->revAdjVex(), node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			if (len > curlength)
			{
				curlength = len;
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
		}
	}

}

void WordMost::letterMostCertainHeadSearchLargeScale(char a)
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist, lastarclist;
	vector<ArcNode> qlist, lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(), lasttime = clock();
	int vexnum;
	int arcnum;
	int len;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = a-'a';
			randDSearch(arclist, qlist, v[vexnum], node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			curlength = len;
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
			if (clock() - starttime >= timelimit)
				return;
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit / 50)
		{
			if (qlist.size() == 1)
				arcnum = 0;
			else
				arcnum = qlist.size() - rand() % (qlist.size() / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			for (int j = arcnum; j < arclist.size(); j++)
			{
				arclist[j]->clearStar();
			}
			Arc *removearc = arclist[arcnum];
			arclist.erase(begin(arclist) + arcnum, end(arclist));

			randDSearch(arclist, qlist, removearc->revAdjVex(), node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			if (len > curlength)
			{
				curlength = len;
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
		}
	}
}

void revDSearch(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
{
	int flag = 0;
	/*cout << vex.getName() << " " << vex.revAdjArcsPtr().size() << endl;
	wm->getGraph().print();*/
	for (int i = 0; i < vex.revAdjArcsPtr().size(); i++)
	{
		if (vex.revAdjArcsPtr()[i]->isStar() == false)
		{
			/*cout << vex.adjArcs()[i].getName() << endl;*/
			flag = 1;
			vex.revAdjArcsPtr()[i]->setStar();
			node.depth = depth;
			node.value = vex.revAdjArcsPtr()[i]->getName();
			qlist.push_back(node);
			revDSearch(qlist, depth + 1, vex.revAdjArcsPtr()[i]->revAdjVex(), node, wm);
			vex.revAdjArcsPtr()[i]->clearStar();
			qlist.pop_back();
			/*for(int i=0; i<qlist.size() ; i++)
				cout << qlist[i].value << " ";
			cout << endl;*/
		}
	}
	if (flag == 0)
	{
		if (depth - 1 > wm->getMaxlength())
		{
			wm->setMaxLength(depth - 1);
			wm->setQlist(qlist);
			wm->revQlist();
		}
	}
}

void WordMost::certainTailSearch(char tail)
{
	setMaxLength(-1);
	graph.clearAllStar();
	vector<ArcNode> qlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	revDSearch(qlist, 1, v[tail - 'a'], node, this);
	graph.clearAllStar();
	
}

void revRandDSearch(vector<Arc *> &arclist, vector<ArcNode> &qlist, Vertex &vex, ArcNode &node)
{
	vector<int> arcArray;
	for (int i = 0; i < vex.revAdjArcsPtr().size(); i++)
	{
		if (vex.revAdjArcsPtr()[i]->isStar() == false)
		{
			arcArray.push_back(i);
		}
	}
	/*cout <<"vex " << vex.getName() << " " <<  " arcArray = " << arcArray.size() << endl;*/
	if (arcArray.size() == 0)
	{
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
		return;
	}
	else
	{
		int rnum = rand() % arcArray.size();
		vex.revAdjArcsPtr()[arcArray[rnum]]->setStar();
		arclist.push_back(vex.revAdjArcsPtr()[arcArray[rnum]]);
		node.value = vex.revAdjArcsPtr()[arcArray[rnum]]->getName();
		qlist.push_back(node);
		revRandDSearch(arclist, qlist, vex.revAdjArcsPtr()[arcArray[rnum]]->revAdjVex(), node);
	}
}

void WordMost::certainTailSearchLargeScale(char tail)
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist, lastarclist;
	vector<ArcNode> qlist, lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(), lasttime = clock();
	int vexnum;
	int arcnum;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = tail - 'a';
			revRandDSearch(arclist, qlist, v[vexnum], node);
			curlength = qlist.size();
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
				revQlist();
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
			if (clock() - starttime >= timelimit)
				return;
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit / 50)
		{
			if (curlength > 20)
				arcnum = curlength - rand() % 10 - 1;
			else if (curlength == 1)
				arcnum = 0;
			else
				arcnum = curlength - rand() % (curlength / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			Arc *removearc = arclist[arcnum];
			for (int j = arcnum; j < curlength; j++)
			{
				arclist[j]->clearStar();
			}
			arclist.erase(begin(arclist) + arcnum, end(arclist));

			revRandDSearch(arclist, qlist, removearc->adjVex(), node);
			if (qlist.size() > curlength)
			{
				curlength = qlist.size();
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
			revQlist();
		}
	}
}

void WordMost::letterMostCertainTailSearch(char tail)
{
	setMaxLength(-1);
	graph.clearAllStar();
	vector<ArcNode> qlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	revDSearch2(qlist, 0, v[tail - 'a'], node, this);
	graph.clearAllStar();
}

void WordMost::letterMostCertainTailSearchLargeScale(char tail)
{
	srand(time(0));
	setMaxLength(-1);
	graph.clearAllStar();
	vector<Arc *> arclist, lastarclist;
	vector<ArcNode> qlist, lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(), lasttime = clock();
	int vexnum;
	int arcnum;
	int curlength;
	int len;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			qlist.clear();
			arclist.clear();
			vexnum = tail - 'a';
			revRandDSearch(arclist, qlist, v[vexnum], node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			curlength = len;
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
				revQlist();
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
			if (clock() - starttime >= timelimit)
				return;
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit / 50)
		{
			if (qlist.size() > 20)
				arcnum = qlist.size() - rand() % 10 - 1;
			else if (qlist.size() == 1)
				arcnum = 0;
			else
				arcnum = qlist.size() - rand() % (qlist.size() / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));
			Arc *removearc = arclist[arcnum];
			for (int j = arcnum; j < qlist.size(); j++)
			{
				arclist[j]->clearStar();
			}
			arclist.erase(begin(arclist) + arcnum, end(arclist));

			revRandDSearch(arclist, qlist, removearc->adjVex(), node);
			len = 0;
			for (int j = 0; j < arclist.size(); j++)
				len += arclist[j]->getLength();
			if (len > curlength)
			{
				curlength = len;
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
			revQlist();
		}
	}
}