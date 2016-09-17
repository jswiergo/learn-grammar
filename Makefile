CXX = g++
CXX_FLAGS = -Wall

PROGRAMS = filterWordPairs countWordPairs

.PHONY: all clean

all: $(PROGRAMS)

clean:
	rm -f *~ $(PROGRAMS)

filterWordPairs: filterWordPairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS)

countWordPairs: countWordPairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS)
