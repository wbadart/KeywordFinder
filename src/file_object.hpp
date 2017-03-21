/**
 * file_object.hpp
 *
 * Load files into vectors of lines, compute
 * sets of tokens.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#ifndef _H_FILEOBJECT
#define _H_FILEOBJECT

#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class FileObject{

    friend std::ostream& operator<<(std::ostream&, const FileObject&);

	public:

        // Constructor takes target filename
		FileObject(std::string _fname);

        // Deconstructor, nothing special
		~FileObject();

        // Return the lines of the file as vector
        std::vector<std::string> get_lines();

        // Get a set of unique tokens (whole file or line)
        std::set<std::string> get_tokens();
        std::vector<std::string> get_tokens(std::string);

	private:

        // Name of corresponding file
        std::string fname;

        // List of lines
        std::vector<std::string> lines;
};

#endif

