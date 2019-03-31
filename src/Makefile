CXX=g++
CFLAGS=-O3 -Wall
Wordlist: InputParser.o readFile.o WordGraph.o Wordlist.o findAllWordList.o findAllCharList.o DebugTime.o WordMost.o
	$(CXX) $^ -o $@ 
	
.PHONY: clean

clean:
	-rm -f *.o Wordlist solution.txt
