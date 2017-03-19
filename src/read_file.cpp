#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "read_file.h"

using namespace std;

FileObj::FileObj(string f){
	filename = f;
	vector<string> items;
	load_items();
}

FileObj::~FileObj(){}

void FileObj::load_items(){
	ifstream myfile(filename);
	string line;
	while(getline(myfile, line)){
		items.push_back(line);
	}
	myfile.close();	
}

vector<string> FileObj::get_items(){
	return items;
}

void FileObj::print_items(){
	for(unsigned i = 0; i < items.size(); i++){
		cout << items[i];
	}
}
