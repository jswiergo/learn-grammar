CXX = g++
CXX_FLAGS = -Wall

PROGRAMS = filterWordPairs

.PHONY: all clean

all: $(PROGRAMS)

clean:
	rm -f *~ $(PROGRAMS)

filterWordPairs: filterWordPairs.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS)
