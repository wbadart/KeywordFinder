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

set<string> FileObj::to_set(){
    set<string> result;
    for(string line: items){
        stringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss}
                            , istream_iterator<string>{}};
        for(string t: tokens)
            result.insert(t);
    }
    return result;
}

