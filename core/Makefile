CXX=g++
CFLAGS=-O3 -Wall

test: WordGraph.o test.o WordMost.o gen_chain_word_n.o gen_chain_char_n.o CharChain.o WordChain.o 
	$(CXX) $^ -o $@ 
	
.PHONY: clean

clean:
	-rm -f *.o test
