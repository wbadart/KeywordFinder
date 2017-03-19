##
# Makefile
#
# Build instructions for project 4 program. Also
# includes unit tests.
#
# Badart, Cat
# Badart, Will
# created: MAR 2017
##

CXX  	  = g++
CXX_FLAGS = -Wall -ggdb

LD 	     = g++
LD_FLAGS =

MAIN  = main
OBJS  = main.o config.o read_file.o
TESTS =


all: $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $(MAIN)

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ -c

clean:
	@rm -f $(MAIN) *.o

test: $(TESTS)
	@echo "Tests complete."

