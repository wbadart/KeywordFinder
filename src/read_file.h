#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FileObj {
	public:
		FileObj(string);
		~FileObj();
		vector<string> get_items();
        set<string> to_set();
		void print_items();
	private:
		void load_items();
		string filename;
		vector<string> items;
};
