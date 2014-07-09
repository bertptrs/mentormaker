CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O2 -std=c++11 -g
LDFLAGS=
RM=rm -rf
MKDIR=mkdir -p

VPATH=src/

OBJDIR=bin
DATADIR=data

DIRS=$(OBJDIR) \
	 $(DATADIR)

RANDOMINPUT=data/random.csv

_OBJS=mentormaker.o\
	  Sjaars.o\
	  Solver.o\
	  Group.o\
	  Solution.o\
	  HillClimbSolver.o

OBJS=$(patsubst %, $(OBJDIR)/%, $(_OBJS))

DEPFILE=Makefile.depend

CPPFILES=$(wildcard src/*.cpp)

.PHONY: all clean test

all: mentormaker

test: all $(RANDOMINPUT)
	./mentormaker $(RANDOMINPUT)

$(RANDOMINPUT): generator | $(DIRS)
	./$< 200 $@

$(DIRS):
	$(MKDIR) $@

clean:
	$(RM) mentormaker
	$(RM) generator
	$(RM) $(DEPFILE)
	$(RM) $(DIRS)

run: all
	./test
	eog result.ppm &

$(DEPFILE): $(CPPFILES)
	gcc $(CXXFLAGS) -MM $^ > $@ 2> /dev/null

mentormaker: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	
generator: generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

include $(DEPFILE)
