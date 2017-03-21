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

OBJS  = main.o config.o read_file.o web.o parser.o
TESTS = test-usage test-get


all: $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $(OUT)

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ -c

clean:
	@rm -f $(OUT) *.o tmp_*

test: $(TESTS)
	@echo "Tests complete."

test-usage: all
	./$(OUT) --help

test-get: all
	@echo "http://example.com" > tmp_sites
	@echo "SITE_FILE=tmp_sites" > tmp_config
	./$(OUT) tmp_config 2> /dev/null | awk -F: '/web_result/ { print $$3 }' | xargs test -s

