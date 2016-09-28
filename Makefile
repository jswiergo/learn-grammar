CXX = g++
CXX_FLAGS = -Wall -std=c++11
LD_FLAGS= -llink-grammar

PROGRAMS = parseWordPairs countWordPairs mergeWordPairs calcWordPairsMI

.PHONY: all clean

all: $(PROGRAMS)

clean:
	rm -f *~ *.o $(PROGRAMS)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXX_FLAGS)

parseWordPairs: parseWordPairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LD_FLAGS)

countWordPairs: countWordPairs.cc wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

mergeWordPairs: mergeWordPairs.cc wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

calcWordPairsMI: calcWordPairsMI.cc wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)
