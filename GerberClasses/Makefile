CC = clang
CXX = clang++
CXXFLAGS = -std=c++11

objects := $(patsubst %.cc, %.o, $(wildcard *.cc))

all: $(objects)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -g $<

clean:
	rm -rf *.o