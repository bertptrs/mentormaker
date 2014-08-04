CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O2 -std=c++11 -g
LDFLAGS=
DISTLDFLAGS=$(LDFLAGS) -static-libgcc -static-libstdc++
RM=rm -rf
MKDIR=mkdir -p

VPATH=src/

OBJDIR=bin
DATADIR=data
DEPDIR=deps
DISTDIR=dist

DIRS=$(OBJDIR) \
	 $(DATADIR) \
	 $(DEPDIR) \
	 $(DISTDIR)

RANDOMINPUT=data/random.in.csv
RANDOMOUTPUT=data/random.out.csv

_OBJS=mentormaker.o\
	  Sjaars.o\
	  Solver.o\
	  Group.o\
	  Solution.o\
	  HillClimbSolver.o

OBJS=$(patsubst %, $(OBJDIR)/%, $(_OBJS))
DEPS=$(patsubst %.o, $(DEPDIR)/%.depend, $(_OBJS))

CPPFILES=$(wildcard src/*.cpp)

.PHONY: all clean test distributables

all: mentormaker

test: all $(RANDOMINPUT)
	./mentormaker $(RANDOMINPUT) $(RANDOMOUTPUT)

$(RANDOMINPUT): generator | $(DIRS)
	./$< 200 $@

distributables: dist/generator dist/mentormaker

dist/generator: generator.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) $(DISTLDFLAGS) -o $@ $<

dist/mentormaker: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DISTLDFLAGS) -o $@ $^

$(DIRS):
	$(MKDIR) $@

clean:
	$(RM) mentormaker
	$(RM) generator
	$(RM) $(DIRS)

run: all
	./test
	eog result.ppm &

$(DEPFILE): $(CPPFILES)
	gcc $(CXXFLAGS) -MM $^ -MF $@

mentormaker: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	
generator: generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(DEPDIR)/%.depend: %.cpp | $(DIRS)
	$(CXX) -MM -MG -MT $(OBJDIR)/$(basename $(notdir $<)).o -MF $@ $<

include $(DEPS)
