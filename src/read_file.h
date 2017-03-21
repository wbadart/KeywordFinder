#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

class FileObj {
	public:
		FileObj(string);
		~FileObj();
		vector<string> get_items();
        set<string> to_set();
        map<string, unsigned> to_count(set<string> terms);
		void print_items();
	private:
		void load_items();
		string filename;
		vector<string> items;
};
