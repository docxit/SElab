CXX=g++
CFLAGS=-O3 -Wall

all: lib lib/core.a lib/core.h test

lib/core.a: WordGraph.o WordMost.o gen_chain_word_n.o gen_chain_char_n.o CharChain.o WordChain.o lib
	ar -r $@ WordGraph.o WordMost.o gen_chain_word_n.o gen_chain_char_n.o CharChain.o WordChain.o
	
lib/core.h: lib
	cp core.h lib/core.h
	
test: test.o lib/core.a
	$(CXX) -o $@ $^
	
lib: 
	mkdir -p lib
	
.PHONY: clean

clean:
	-rm -rf *.o test lib
