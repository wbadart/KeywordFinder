/**
 * main.cpp
 *
 * Entry file of project program.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */
#include <iostream>
#include <string>
#include <vector>

#include "read_file.h"

using namespace std;

int main(int argc, char *argv[]){
    FileObj SitesFile("ExampleSites.txt");
	SitesFile.print_items();
	return 0;
}

