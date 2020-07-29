# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main 

main: main.cpp Football.o
	$(CXX) $(CXXFLAGS) main.cpp Football.o -o main

Football.o: Football.cpp Football.h
	$(CXX) $(CXXFLAGS) -c Football.cpp -o Football.o

deepclean: 
	rm -f *~ *.o main *.exe *.stackdump main

clean:
	-rm -f *~ *.o *.stackdump

