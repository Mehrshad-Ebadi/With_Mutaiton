BASE = $(shell pwd)

CC=gcc
#OBJFLAGS+=-Wall -Wextra -O0 -g -D_GLIBCXX_DEBUG -c
OBJFLAGS+=-O0 -g -D_GLIBCXX_DEBUG -c

INC = ./Headers/Genome.hpp
CPP = ./Functions
LIB = ./Library/MD_V.a

#CCS = $(shell ls $(CPP))
FUNCS = ./Functions/*.cpp
OBJS = ./*.o
#FUNCS = $(CCS:%.cpp=$(CPP)/%.cpp)
#OBJS = $(CCS:.cpp=.o)

OUT = ./Results
#plot = ./plotter
MAIN = ./Main/Main.cpp
EXE =./Exe


Run: FCompile

	@echo "Ready to fire..."
Objects:
	@echo "Compiling Functions..."	
	@$(CC) $(OBJFLAGS) $(FUNCS) 

LiBuild: Objects
	@echo "Building Library..."	
	@rm -f $(LIB)
	@ar ruv $(LIB) $(OBJS)
	@ranlib $(LIB)
	@rm -f $(OBJS)

FCompile: LiBuild
	@echo "Final Packing..."	
	@rm -r $(EXE)
	@mkdir $(EXE)
	@$(CC) -o Final.out $(INC) $(MAIN) $(LIB)
	@mv ./Final.out $(EXE)/Final.out
