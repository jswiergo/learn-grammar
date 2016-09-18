CXX = g++
CXX_FLAGS = -Wall -std=c++11

PROGRAMS = filterWordPairs countWordPairs mergeWordPairs

.PHONY: all clean

all: $(PROGRAMS)

clean:
	rm -f *~ *.o $(PROGRAMS)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXX_FLAGS)

filterWordPairs: filterWordPairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS)

countWordPairs: countWordPairs.cc wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)

mergeWordPairs: mergeWordPairs.cc wordPairs.o
	$(CXX) -o $@ $^ $(CXX_FLAGS)
