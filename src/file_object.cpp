/**
 * file_object.cpp
 *
 * Implemetation of file wrapper.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include "file_object.hpp"

FileObject::FileObject(std::string _fname):fname(_fname){
    std::ifstream ifs(fname); std::string line;
    // If we need to strip the trailing whitespace:
    /* line.erase(line.find_last_not_of(" \n\r\t")+1); */
    while(getline(ifs, line))
        lines.push_back(line);
    ifs.close();
}

FileObject::~FileObject(){}
std::vector<std::string> FileObject::get_lines(){return lines;}

std::set<std::string> FileObject::get_tokens(){
    std::set<std::string> result;
    for(std::string line: lines){
        std::vector<std::string> words = get_tokens(line);
        result.insert(words.begin(), words.end());
    }
    return result;
}

std::vector<std::string> FileObject::get_tokens(std::string line){
    std::stringstream iss(line);
    return std::vector<std::string>{
        std::istream_iterator<std::string>{iss}
      , std::istream_iterator<std::string>{}};
}

size_t FileObject::size(){
    return lines.size();
}

std::string FileObject::operator[](size_t i){
    return lines[i];
}

std::ostream& operator<<(std::ostream& stream, const FileObject& f){
    for(std::string line: f.lines)
        stream << line << std::endl;
    return stream;
}

std::vector<std::string>::iterator FileObject::begin(){
    return lines.begin();}
std::vector<std::string>::iterator FileObject::end(){
    return lines.end();}

