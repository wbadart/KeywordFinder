# OS Project 4
## Web Crawler

This program can be used to verify the success of SEO efforts by scanning target sites for keywords.

## Team

- Badart, Cat (netid: *cbadart*)
- Badart, Will (netid: *wbadart*)

## Building and running

To build the program, run `make`. The Makefile has been configured to run with a specific version of `g++` which is available on the student machines. The program has been tested and verified on `student00`. To run some simple automatic tests, run `make test`, which will generate a short config file and sample search/ sites files. You may provide your own configuration files so long as they are compliant with the requirements specified in the project document (invalid parameters result in a warning, and not-found config files result in a graceful exit).

In the config file, if you enter more than the max number of threads (8), an error message is printed but NUM_FETCH and/or NUM_PARSE is set to 8 and the program continues.  Likewise, if the number of threads is less than 1, an error message is printed and the number of threads is set to 1.

## Output

While the program is running, it will emit a number of temporary files and a single report per period. You may ignore the temporary files (all of which are dumped to `/tmp`). Each run through the main loop will result in a file called `N.csv`, where `N` is the number of that period. The format of that file is in accordance with the format specified in the project document.

Also emitted each period are `index.html` and `script.js` (note that these are overwritten with the new data each period). Opening `index.html` in a browser will show a graphical summary of the parsing results, powered by [highcharts](http://highcharts.com).

## Internals

Under the hood, the program establishes a pipeline of task queues, following an architecture inspired by map-reduce. The pipeline is set up as a linked list such that each sequential task queue knows to which queue it must send its data. Threading occurs at the queue level, e.g. if NUM_FETCH is set to 4, the program will fetch up to 4 sites at a time, and only move on to parsing once all sites have been fetched. Likewise, `main` will wait until the last queue (the queue with no `next`) has finished, until it unblocks.

