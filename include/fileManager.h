#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>  

using std::vector;
using std::string;

class FileManager {
public:
    bool writeFile(string fileName, string text);
    vector<string> readFile(string fileName);
    vector<string> split(string text, char token);
private:
    string _text;
};


#endif