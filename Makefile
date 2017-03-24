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
CXX_FLAGS = -Wall -ggdb -std=gnu++11

LD 	     = g++
LD_FLAGS = -lcurl -lpthread -static-libstdc++

OBJS  = main.o config.o file_object.o web.o parser.o task_queue.o
TESTS = test-usage test-fetch test-parse


all: $(OBJS) link

link:
	$(LD) $(LD_FLAGS) $(OBJS) -o $(OUT)

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@ -c

clean:
	@rm -f $(OUT) *.o tmp_*

test: $(TESTS)
	@echo "Tests complete."

test-usage: all test-mkfiles
	./$(OUT) --help

test-fetch: all test-mkfiles
	./$(OUT) tmp_config 2> /dev/null | awk -F: '/web_result/ { print $$3 }' | xargs test -s

test-parse: all test-mkfiles
	./$(OUT) tmp_config 2> /dev/null | grep -Pq '^parse.Found'

test-mkfiles:
	@echo "http://example.com" > tmp_sites
	@echo "http://cnn.com" >> tmp_sites
	@echo "http://nytimes.com" >> tmp_sites
	@echo "http://nd.edu/~wbadart" >> tmp_sites
	@echo "examples" > tmp_search
	@echo "SITE_FILE=tmp_sites" > tmp_config
	@echo "SEARCH_FILE=tmp_search" >> tmp_config

