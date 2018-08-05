#include "../include/fileManager.h"
#include <iostream>

using std::cout;
using std::endl;

bool FileManager::writeFile(string fileName, string text) {
    std::ofstream file;
    file.open (fileName);
    file << text;
    file.close();
    return true;    
}

vector<string> FileManager::readFile(string fileName) {
    string line;
    std::ifstream myfile (fileName);
    vector<string> result = { };

    if (!myfile.is_open())
        return result;

    while ( getline (myfile,line) )
        result.push_back(line);   
    myfile.close();
    return result;
}

vector<string> FileManager::split(string text, char token) {
    vector<string> result;
    std::stringstream ss(text);
    string tok;
    while(getline(ss, tok, token))
        result.push_back(tok);
    return result;
}
