#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "FileHandler.h"

std::fstream fileToWorkWith;

void FileHandler::file_opener(){
    char filename[ ] = "game_data.txt";

    fileToWorkWith.open(filename, std::fstream::in | std::fstream::out);

    // If file does not exist, Create new file
    if (!fileToWorkWith ) 
    {
        std::cout << "Cannot open file, file does not exist. Creating new file..";
        fileToWorkWith.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    } 
}

int* FileHandler::read_file(int * data){
    std::string line;
    std::vector<std::string> v;

    if(!fileToWorkWith.is_open()){
        file_opener();    
    }
    int i = 0;
    getline(fileToWorkWith, line);
    boost::split(v,line, boost::is_any_of(","));
    for(size_t i = 0; i < v.size(); i++){
        data[i] = atoi(v[i].c_str());
    }
    fileToWorkWith.close();
    return data;
}

void FileHandler::write_to_file(std::string result){
    if(!fileToWorkWith.is_open()){
        file_opener();    
    }
    fileToWorkWith << result;
    fileToWorkWith.close();
}