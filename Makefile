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
TESTS =


all: main.o
	$(CXX) $(CXX_FLAGS) $< -o $(MAIN)

test: $(TESTS)
	@echo "Tests complete."

