#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileObj {
	public:
		FileObj(string);
		~FileObj();
		void load_items();
		vector<string> get_items();
	private:
		string filename;
		vector<string> items;
};
