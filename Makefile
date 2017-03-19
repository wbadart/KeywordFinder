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

OUT = site-tester

CXX  	  = g++
CXX_FLAGS = -Wall -ggdb

LD 	     = g++
LD_FLAGS = -lcurl

OBJS  = main.o config.o read_file.o web.o
TESTS = test-usage


all: $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $(OUT)

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ -c

clean:
	@rm -f $(OUT) *.o

test: $(TESTS)
	@echo "Tests complete."

test-usage: all
	./$(OUT) --help

