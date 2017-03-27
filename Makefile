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

CXX  	  = /afs/nd.edu/user14/csesoft/new/bin/g++
CXX_FLAGS = -Wall -ggdb -std=gnu++11

LD 	     = /afs/nd.edu/user14/csesoft/new/bin/g++
LD_FLAGS = -lcurl -lpthread -static-libstdc++

OBJS  = main.o config.o file_object.o web.o parser.o task_queue.o
TESTS = test-usage test-fetch test-parse


all: $(OBJS) link

link:
	$(LD) $(LD_FLAGS) $(OBJS) -o $(OUT)

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ -c

clean:
	@rm -f $(OUT) *.{o,csv,html,js} tmp_*

# Run all tests
test: $(TESTS)
	@echo "Tests successful."

# Test that program reports usage message
test-usage: all test-mkfiles
	./$(OUT) --help

# Check that fetch result files exist and aren't empty
test-fetch: all test-mkfiles
	timeout -s INT 10 ./$(OUT) tmp_config 2> /dev/null | awk -F: '/web_result/ { print $$3 }' | test -s

# Check that parse result files exist and aren't empty
test-parse: all test-mkfiles
	timeout -s INT 10 ./$(OUT) tmp_config 2> /dev/null | awk -F' ' '/parse_result/ { print $$4 }' | test -s

# Create temporary config files
test-mkfiles:
	@echo "http://example.com" > tmp_sites
	@echo "http://cnn.com" >> tmp_sites
	@echo "http://nytimes.com" >> tmp_sites
	@echo "http://nd.edu/~wbadart" >> tmp_sites
	@echo "examples" > tmp_search
	@echo "student" >> tmp_search
	@echo "SITE_FILE=tmp_sites" > tmp_config
	@echo "SEARCH_FILE=tmp_search" >> tmp_config
	@echo "PERIOD_FETCH=8" >> tmp_config

