CXX = g++
CXX_FLAGS = -Wall -std=c++11
LD_FLAGS= -llink-grammar

PROGRAMS = parseWordPairs \
           parseWordIndexes \
           sumUniquePairs \
           countWordPairs \
           mergeWordPairs \
           calcWordPairsMI \
           parseDisjucts

.PHONY: all clean

all: $(PROGRAMS)

clean:
	rm -f *~ *.o $(PROGRAMS)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXX_FLAGS)

parseWordPairs: parseWordPairs.cc linkGrammar.o
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LD_FLAGS)

parseWordIndexes: parseWordIndexes.cc linkGrammar.o words.o
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LD_FLAGS)

sumUniquePairs: sumUniquePairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS)

countWordPairs: countWordPairs.cc words.o wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

mergeWordPairs: mergeWordPairs.cc words.o wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

calcWordPairsMI: calcWordPairsMI.cc words.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

parseDisjucts: parseDisjuncts.cc words.o wordPairs.o disjunct.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)
