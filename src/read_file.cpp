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
        line.erase(line.find_last_not_of(" \n\r\t")+1);
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
    return set<string>{items.begin(), items.end()};
}

map<string, unsigned> FileObj::to_count(set<string> terms){
    map<string, unsigned> result;
    for(string t: terms){
        cerr << t << endl;
        result[t] = 0;
    }
    for(string line: items){
        stringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss}
                            , istream_iterator<string>{}};
        for(string t: tokens)
            if(terms.count(t)) result[t]++;
    }
    return result;
}

