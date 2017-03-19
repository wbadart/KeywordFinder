#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "read_file.h"

using namespace std;

FileObj::FileObj(string f){
	filename = f;
	vector<string> items;
}

FileObj::~FileObj(){}

void FileObj::load_items(){
	ifstream myfile(filename);
	string line;
	while(getline(myfile, line)){
		items.push_back(line);
	}
	myfile.close()	
}
